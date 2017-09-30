#include "usb_communication.h"

#include "ch.h"
#include "hal.h"
#include "hal_streams.h"
#include "usbcfg.h"
#include "board.h"
#include "ringbuffer.h"
#include "leds.h"

static THD_WORKING_AREA(usb_com_rx_wa, 256);
static THD_WORKING_AREA(usb_com_tx_wa, 256);
static THD_FUNCTION(usb_rx_thd, arg);
static THD_FUNCTION(usb_tx_thd, arg);

static const uint8_t Start1Value = 0x55;
static const uint8_t Start2Value = 0xDA;

// together with oca_usb_get_data_frame this makes a very basic circular buffer
#define DATA_FRAME_BUFFER_SIZE 5
oca_usb_data_frame data_frame_buffer[DATA_FRAME_BUFFER_SIZE];

static msg_t rx_data_frame_mailbox_queue[DATA_FRAME_BUFFER_SIZE];
static mailbox_t rx_data_frame_mailbox;

oca_usb_data_frame* oca_usb_decode_stream(ring_buffer_t* ring_buf);
oca_usb_data_frame* oca_usb_get_data_frame(void);

ring_buffer_t ring_buffer_rx;
ring_buffer_t ring_buffer_tx;
/*
 * DP resistor control is not possible on the STM32F3-Discovery, using stubs
 * for the connection macros.
 */
 #define usb_lld_connect_bus(usbp)
 #define usb_lld_disconnect_bus(usbp)

void oca_usb_init(void)
{
	ring_buffer_init(&ring_buffer_rx);
	ring_buffer_init(&ring_buffer_tx);

	chMBObjectInit(&rx_data_frame_mailbox, rx_data_frame_mailbox_queue, DATA_FRAME_BUFFER_SIZE);
	/*
	 * Initializes a serial-over-USB CDC driver.
	 */
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);
	
	/*
	 * Activates the USB driver and then the USB bus pull-up on D+.
	 * Note, a delay is inserted in order to not have to disconnect the cable
	 * after a reset.
	 */
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

	chThdCreateStatic(usb_com_rx_wa, sizeof(usb_com_rx_wa), NORMALPRIO, usb_rx_thd, NULL);
	chThdCreateStatic(usb_com_tx_wa, sizeof(usb_com_tx_wa), NORMALPRIO, usb_tx_thd, NULL);
}

void oca_usb_queue_data_frame(oca_usb_data_frame* frame)
{
	// if the buffer overflows there is probably something wrong with comms
	if(ring_buffer_is_full(&ring_buffer_tx))
		ring_buffer_init(&ring_buffer_tx);

		ring_buffer_queue(&ring_buffer_tx, Start1Value);
		ring_buffer_queue(&ring_buffer_tx, Start2Value);
		ring_buffer_queue(&ring_buffer_tx, frame->dataSize);
		ring_buffer_queue_arr(&ring_buffer_tx, frame->data, frame->dataSize);
}

static THD_FUNCTION(usb_rx_thd, arg)
{
	(void)arg;
	chRegSetThreadName("usb_rx_thd");
	while (true) {
		if(serusbcfg.usbp->state == USB_ACTIVE)
		{
			if(SDU1.state == SDU_READY)
			{
				uint8_t readVal;

				if(chnRead(&SDU1, &readVal, 1) > 0)
				{
					ring_buffer_queue(&ring_buffer_rx, readVal);
			
					oca_usb_data_frame* frame = oca_usb_decode_stream(&ring_buffer_rx);
					if(frame != NULL)
					{                 
						chMBPost(&rx_data_frame_mailbox, (msg_t)frame, MS2ST(100));
						oca_usb_queue_data_frame(frame);	//echo back the frame as a test
						oca_led_toggle(oca_led_act);
					}
				}
			}
		}
		else
		{
			chThdSleepMilliseconds(100);	//When not connected poll every 100ms
		}
	}
}

static THD_FUNCTION(usb_tx_thd, arg)
{
	(void)arg;
	chRegSetThreadName("usb_tx_thd");
	char sendBufferData[RING_BUFFER_SIZE];

	while (true) {
		if(serusbcfg.usbp->state == USB_ACTIVE)
		{
			if(SDU1.state == SDU_READY)
			{
				uint8_t len = ring_buffer_num_items(&ring_buffer_tx);
				if(len > 0)
				{
					ring_buffer_dequeue_arr(&ring_buffer_tx, sendBufferData, len);
					chnWrite(&SDU1, (uint8_t*)sendBufferData, len);
				}
				chThdSleepMilliseconds(100);
			}
		}
		else
		{
			chThdSleepMilliseconds(100);	//When not connected poll every 100ms
		}
	}
}

oca_usb_data_frame* oca_usb_decode_stream(ring_buffer_t* ring_buf)
{
	bool StartFound = false;
	uint8_t FrameSize = 0;
	uint8_t FrameLocation = 0;

	uint8_t len = ring_buffer_num_items(ring_buf);
	if(len < 3)
		return NULL;

	// Find the header of the frame
	// 0x55 0xDA <size>
	for(uint8_t i = 0; i<len; i++)
	{
		if((len - i) >= 3)
		{
			char BufStart1, BufStart2, BufSize;
			ring_buffer_peek(ring_buf, &BufStart1, i+0);
			ring_buffer_peek(ring_buf, &BufStart2, i+1);
			ring_buffer_peek(ring_buf, &BufSize, i+2);
			if(BufStart1 == Start1Value && BufStart2 == Start2Value)
			{
				StartFound = true;
				FrameSize = BufSize;
				FrameLocation = i+3;
				break;
			}
		}
	}

	// Found the header now look of the required data is already 
	// in the buffer
	if(StartFound)
	{
		if(len-FrameLocation >= FrameSize)
		{
			char Header[3];
			oca_usb_data_frame* frame = oca_usb_get_data_frame();

			ring_buffer_dequeue_arr(ring_buf, Header, 3); //dequeue header first
			frame->dataSize = FrameSize;
			ring_buffer_dequeue_arr(ring_buf, frame->data, FrameSize);

			return frame;
		}
	}

	return NULL;
}

oca_usb_data_frame* oca_usb_get_data_frame(void)
{
	static int index = 0;
	oca_usb_data_frame* ret = &data_frame_buffer[index];

	index++;
	if(index == DATA_FRAME_BUFFER_SIZE)
		index = 0;

	return ret;
}
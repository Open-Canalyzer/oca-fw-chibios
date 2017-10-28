/*
		ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

		Licensed under the Apache License, Version 2.0 (the "License");
		you may not use this file except in compliance with the License.
		You may obtain a copy of the License at

				http://www.apache.org/licenses/LICENSE-2.0

		Unless required by applicable law or agreed to in writing, software
		distributed under the License is distributed on an "AS IS" BASIS,
		WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
		See the License for the specific language governing permissions and
		limitations under the License.
*/
#include <stdlib.h>

#include "ch.h"
#include "hal.h"
#include "usbcfg.h"
#include "board.h"
#include "leds.h"
#include "usb_communication.h"
#include "chschd.h"

#include "chprintf.h"

#include <pb_encode.h>
#include "protocols.pb.h"

/*
 * 500KBaud, automatic wakeup, automatic recover
 * from abort mode.
 * See: http://www.chibios.com/forum/viewtopic.php?t=1307
 * baudrate=Fclk/((1+BRP)*(3+ts1+ts2)) and APB1 runs at 36MHz
 * 500 000 = (36*10^6)/((1 + 5) * (3 + 5 + 4))
 */
static const CANConfig cancfg = {
	CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,	
	CAN_BTR_SJW(0) | CAN_BTR_TS2(4) | CAN_BTR_TS1(5) | CAN_BTR_BRP(5) | CAN_BTR_LBKM | CAN_BTR_SILM	//loopback and silent mode enabled
};
// The loopback and silent mode fully disconnect the CAN transceiver

static const uint8_t buf[] =
			"Ping\n\r";

/*
 * Receiver thread.
 */
static THD_WORKING_AREA(can_rx_wa, 256);
static THD_FUNCTION(can_rx, p) {
  event_listener_t el;
  CANRxFrame rxmsg;

  (void)p;
  chRegSetThreadName("receiver");
  chEvtRegister(&CAND1.rxfull_event, &el, 0);
  while (true) {
    if (chEvtWaitAnyTimeout(ALL_EVENTS, MS2ST(100)) == 0)
      continue;
    while (canReceive(&CAND1, CAN_ANY_MAILBOX, &rxmsg, TIME_IMMEDIATE) == MSG_OK) {
      /* Process message.*/
      oca_led_toggle(oca_led_act);

      CanMessage UsbMessage = CanMessage_init_default;
      UsbMessage.DLC = rxmsg.DLC;
      UsbMessage.RTR = rxmsg.DLC;
      UsbMessage.IDE = rxmsg.IDE;
      UsbMessage.ID = rxmsg.EID;
      UsbMessage.Data1 = rxmsg.data32[0];
      UsbMessage.Data1 = rxmsg.data32[1];

      uint8_t buffer[30];
      pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
      pb_encode(&stream, CanMessage_fields, &UsbMessage);
      

      /*if(serusbcfg.usbp->state == USB_ACTIVE)
      {
      	if(SDU1.state == SDU_READY)
      		chnWrite(&SDU1, buffer, stream.bytes_written);
      }*/


    }
  }
  chEvtUnregister(&CAND1.rxfull_event, &el);
}

/*
 * Transmitter thread.
 */
static THD_WORKING_AREA(can_tx_wa, 256);
static THD_FUNCTION(can_tx, p) {
	CANTxFrame txmsg;

	(void)p;
	chRegSetThreadName("transmitter");
	txmsg.IDE = CAN_IDE_EXT;
	txmsg.EID = 0x01234567;
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = 8;
	txmsg.data32[0] = 0x55AA55AA;
	txmsg.data32[1] = 0x00;

	while (true) {
		txmsg.data32[1] = chVTGetSystemTime();
		msg_t ret = canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, MS2ST(100));
		
		if(ret == MSG_TIMEOUT || ret == MSG_RESET)
			oca_led_toggle(oca_led_err);

		chThdSleepMilliseconds(100);
	}
}

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

	(void)arg;
	chRegSetThreadName("blinker");
	while (true) {
		oca_led_update();
		chThdSleepMilliseconds(250);
	}
}

/*
 * Application entry point.
 */
int main(void) {

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	oca_led_init();

	oca_usb_init();

	canStart(&CAND1, &cancfg);

	//set_led(led_act, led_blink_250);
	oca_led_set(oca_led_stat, oca_led_blink_500);
	//set_led(led_err, led_blink_1000);

	/*
	 * Creates the blinker thread.
	 */
	chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 5, can_rx, NULL);
	chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
	chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO, can_tx, NULL);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state.
	 */
	while (true) {
		chThdSleepSeconds(1);
	}
}

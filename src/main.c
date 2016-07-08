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

#include "chprintf.h"

/*
 * 500KBaud, automatic wakeup, automatic recover
 * from abort mode.
 * See: http://www.chibios.com/forum/viewtopic.php?t=1307
 * baudrate=Fclk/((1+BRP)*(3+ts1+ts2)) and APB1 runs at 36MHz
 * 500 000 = (36*10^6)/((1 + 5) * (3 + 5 + 4))
 */
static const CANConfig cancfg = {
	CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
	CAN_BTR_SJW(0) | CAN_BTR_TS2(4) | CAN_BTR_TS1(5) | CAN_BTR_BRP(5)
};


/*
 * DP resistor control is not possible on the STM32F3-Discovery, using stubs
 * for the connection macros.
 */
#define usb_lld_connect_bus(usbp)
#define usb_lld_disconnect_bus(usbp)

	static const uint8_t buf[] =
			"Ping\n\r";

static void led_toggle_blue(void)
{
	palTogglePad(GPIOB, GPIOB_LED_STAT);
}

static void led_toggle_green(void)
{
	palTogglePad(GPIOB, GPIOB_LED_ACT);
}

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
      palTogglePad(GPIOB, GPIOB_LED_ERR);

      if(serusbcfg.usbp->state == USB_ACTIVE)
      {
      	if(SDU1.state == SDU_READY)
      		chprintf((BaseSequentialStream *)&SDU1, "Received CAN message: %x %x %x\n", rxmsg.EID, rxmsg.data32[0], rxmsg.data32[1]);
      }


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
		canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, MS2ST(100));
		led_toggle_blue();
		chThdSleepMilliseconds(100);
	}
}

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

	(void)arg;
	systime_t time;
	chRegSetThreadName("blinker");
	while (true) {
		time = serusbcfg.usbp->state == USB_ACTIVE ? 100 : 500;

		/* Writing in buffer mode.*/
		/*(void) obqGetEmptyBufferTimeout(&SDU1.obqueue, TIME_INFINITE);
		memcpy(SDU1.obqueue.ptr, buf, sizeof(buf));
		obqPostFullBuffer(&SDU1.obqueue, sizeof(buf));*/

		led_toggle_green();
		chThdSleepMilliseconds(time);
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

	/*
	 * Initializes a serial-over-USB CDC driver.
	 */
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	canStart(&CAND1, &cancfg);

	/*
	 * Activates the USB driver and then the USB bus pull-up on D+.
	 * Note, a delay is inserted in order to not have to disconnect the cable
	 * after a reset.
	 */
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

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

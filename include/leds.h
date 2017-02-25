#ifndef LEDS_H
#define LEDS_H

#include "board.h"

enum oca_led_select
{
	oca_led_act = GPIOB_LED_ACT,
	oca_led_stat = GPIOB_LED_STAT,
	oca_led_err = GPIOB_LED_ERR
};

enum oca_led_state
{
	oca_led_off = 0,
	oca_led_on,
	oca_led_blink_250,
	oca_led_blink_500,
	oca_led_blink_1000
};

void oca_led_init(void);

void oca_led_set(enum oca_led_select led, enum oca_led_state state);
void oca_led_toggle(enum oca_led_select led);

void oca_led_update(void); //call every 250ms


#endif /* LEDS_H */
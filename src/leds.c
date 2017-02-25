#include "leds.h"

#include "ch.h"
#include "hal.h"
#include "board.h"

static struct oca_led
{
	enum oca_led_state act;
	enum oca_led_state stat;
	enum oca_led_state err;
	uint32_t counter;
} g_oca_led;

void oca_led_init(void)
{
	palClearPad(GPIOB, GPIOB_LED_ERR);
	palClearPad(GPIOB, GPIOB_LED_STAT);
	palClearPad(GPIOB, GPIOB_LED_ACT);

	g_oca_led.act = oca_led_off;
	g_oca_led.stat = oca_led_off;
	g_oca_led.err = oca_led_off;
	g_oca_led.counter = 0;
}

void oca_led_set(enum oca_led_select led, enum oca_led_state state)
{
	switch(led)
	{
		case oca_led_act:
			g_oca_led.act = state;
			break;
		case oca_led_stat:
			g_oca_led.stat = state;
			break;
		case oca_led_err:
			g_oca_led.err = state;
			break;
	}

	if(state == oca_led_off)
		palClearPad(GPIOB, led);
	else if(state == oca_led_on)
		palSetPad(GPIOB, led);

}

void oca_led_toggle(enum oca_led_select led)
{
	palTogglePad(GPIOB, led);
}

void oca_led_update(void)
{
	if(g_oca_led.act == oca_led_blink_250) 
		oca_led_toggle(oca_led_act);
	if(g_oca_led.stat == oca_led_blink_250)
		oca_led_toggle(oca_led_stat);
	if(g_oca_led.err == oca_led_blink_250)
		oca_led_toggle(oca_led_err);
	
	if(g_oca_led.counter == 500 || g_oca_led.counter == 1000)
	{
		if(g_oca_led.act == oca_led_blink_500)
			oca_led_toggle(oca_led_act);
		if(g_oca_led.stat == oca_led_blink_500)
			oca_led_toggle(oca_led_stat);
		if(g_oca_led.err == oca_led_blink_500)
			oca_led_toggle(oca_led_err);
	}
	if(g_oca_led.counter >= 1000)
	{
		if(g_oca_led.act == oca_led_blink_1000)
			oca_led_toggle(oca_led_act);
		if(g_oca_led.stat == oca_led_blink_1000)
			oca_led_toggle(oca_led_stat);
		if(g_oca_led.err == oca_led_blink_1000)
			oca_led_toggle(oca_led_err);
		g_oca_led.counter = 0;
		return;		//skip the increment
	}

	g_oca_led.counter += 250;
}
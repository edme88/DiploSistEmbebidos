#include <stdint.h>
#include "bsp.h"
/*
 * main.c
 *  Created on: 19/09/2014
 *  Author: Agus Edme
 */


//---------------------- Seccion de Declaracion de Funciones -------------------------
void blinky_led(uint8_t, uint32_t);
void Delay(volatile uint32_t nCount);

//------------------------------------- MAIN -----------------------------------------
int main(void) {
	bsp_init();

	uint32_t timeL = 0x5FFFF;
	int led_actual;

	while (1) {

		for (led_actual = 0; led_actual < 4; led_actual++) {
			blinky_led(led_actual, timeL);
		}

		if (sw_getState()==1) {
			timeL += timeL/10;
		} else {
			timeL = 0x5FFFF;
		}
	}
}

//------------------------------------- FUNCIONES -----------------------------------
void blinky_led(uint8_t led, uint32_t timeL) {
	led_on(led);
	Delay(timeL);
	led_off(led);
}

void Delay(volatile uint32_t nCount) {
	while (nCount--) {
	}
}

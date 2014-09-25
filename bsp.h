#ifndef __BSP_H
#define __BSP_H
/*
 * bsp.h
 *  Created on: 19/09/2014
 *  Author: Agus Edme
 */



void led_on(uint8_t led);
void led_off(uint8_t led);

uint8_t sw_getState(); //se le podria poner argumentos si hay mas de un switch
void bsp_init();

#endif

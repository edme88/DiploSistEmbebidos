#include "stm32f4xx.h"			// Header del micro
#include "stm32f4xx_gpio.h"		// Perifericos de E/S
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
/* Simple funcion de delay */
void Delay(__IO uint32_t nCount);

/* Inicializa los puertos E/S */
void ES_Init();

// Definiciones de hardware
#define LED_V GPIO_Pin_12
#define LED_N GPIO_Pin_13
#define LED_R GPIO_Pin_14
#define LED_A GPIO_Pin_15

const int leds[4] = { LED_A, LED_V, LED_N, LED_R };

#define BOTON GPIO_Pin_0

void blinky_led(int, uint32_t);

int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// configuro GPIO
	ES_Init();
	uint32_t timeL = 0x5FFFF;
	int led_actual;

	while (1) {

		for (led_actual = 0; led_actual < 4; led_actual++) {
			blinky_led(led_actual, timeL);
		}

		if (GPIO_ReadInputDataBit(GPIOA, BOTON) == 1) {
			timeL += timeL/10;
		} else {
			timeL = 0x5FFFF;
		}
	}
}

void blinky_led(int a, uint32_t timeL) {
	GPIO_SetBits(GPIOD, leds[a]);
	Delay(timeL);
	GPIO_ResetBits(GPIOD, leds[a]);
}

void ES_Init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
			| GPIO_Pin_12;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // (Push/Pull)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	// Arranco el clock del periferico
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Delay(__IO uint32_t nCount) {
	while (nCount--) {
	}
}

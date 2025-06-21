/*
 * NRF24L01.h
 *
 *  Created on: Jun 21, 2025
 *      Author: Eren
 */

#ifndef INC_NRF24L01_H_
#define INC_NRF24L01_H_

#include "main.h"

extern SPI_HandleTypeDef hspi1;

typedef struct{
	GPIO_TypeDef* PORT;
	uint16_t PIN;
}GpioPin;

typedef struct{
	SPI_HandleTypeDef* hspi;
	GpioPin CE;
	GpioPin CS;
}NRF24L01;

#endif /* INC_NRF24L01_H_ */

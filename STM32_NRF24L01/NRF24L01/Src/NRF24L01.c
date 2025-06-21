/*
 * NRF24L01.c
 *
 *  Created on: Jun 21, 2025
 *      Author: Eren
 */
#include <NRF24L01.h>

void CS_Select(NRF24L01* hnrf)
{
	HAL_GPIO_WritePin(hnrf->CS.PORT, hnrf->CS.PIN, GPIO_PIN_RESET);
}

void CS_UnSelect(NRF24L01* hnrf)
{
	HAL_GPIO_WritePin(hnrf->CS.PORT, hnrf->CS.PIN, GPIO_PIN_SET);
}

void CE_Select(NRF24L01* hnrf)
{
	HAL_GPIO_WritePin(hnrf->CE.PORT, hnrf->CE.PIN, GPIO_PIN_SET);
}

void CE_UnSelect(NRF24L01* hnrf)
{
	HAL_GPIO_WritePin(hnrf->CE.PORT, hnrf->CE.PIN, GPIO_PIN_RESET);
}

void nrf24_writeReg(NRF24L01* hnrf, uint8_t address, uint8_t data)
{
	uint8_t buf[2];
	buf[0] = address | (1<<5);
	buf[1] = data;

	// Pull the CS Pin Low to select the device
	CS_Select(hnrf);

	HAL_SPI_Transmit(hnrf->hspi, buf, 2, 1000);

	// Pull the CS Pin High to release the device
	CS_UnSelect(hnrf);
}

void nrf24_writeRegMulti(NRF24L01* hnrf, uint8_t address, uint8_t* data, int size)
{

}

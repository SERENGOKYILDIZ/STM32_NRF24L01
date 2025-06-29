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

void CE_Enable(NRF24L01* hnrf)
{
	HAL_GPIO_WritePin(hnrf->CE.PORT, hnrf->CE.PIN, GPIO_PIN_SET);
}

void CE_Disable(NRF24L01* hnrf)
{
	HAL_GPIO_WritePin(hnrf->CE.PORT, hnrf->CE.PIN, GPIO_PIN_RESET);
}

// Write a single byte to particular register
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

// Write multiple bytes starting from a particular register
void nrf24_writeRegMulti(NRF24L01* hnrf, uint8_t address, uint8_t* data, int size)
{
	uint8_t buf[2];
	buf[0] = address | (1<<5);

	// Pull the CS Pin Low to select the device
	CS_Select(hnrf);

	HAL_SPI_Transmit(hnrf->hspi, buf, 1, 1000);
	HAL_SPI_Transmit(hnrf->hspi, data, size, 1000);

	// Pull the CS Pin High to release the device
	CS_UnSelect(hnrf);
}

// Read a single byte to register
uint8_t nrf24_readReg(NRF24L01* hnrf, uint8_t address)
{
	uint8_t data = 0x00;

	// Pull the CS Pin Low to select the device
	CS_Select(hnrf);

	HAL_SPI_Transmit(hnrf->hspi, &address, 1, 100);
	HAL_SPI_Receive(hnrf->hspi, &data, 1, 100);

	// Pull the CS Pin High to release the device
	CS_UnSelect(hnrf);

	return data;
}

// Read multiple bytes starting from register
void nrf24_readRegMulti(NRF24L01* hnrf, uint8_t address, uint8_t* data, int size)
{
	// Pull the CS Pin Low to select the device
	CS_Select(hnrf);

	HAL_SPI_Transmit(hnrf->hspi, &address, 1, 100);
	HAL_SPI_Receive(hnrf->hspi, data, size, 1000);

	// Pull the CS Pin High to release the device
	CS_UnSelect(hnrf);
}

// Send the command the NRF
void nrf24_sendCmd(NRF24L01* hnrf, uint8_t cmd)
{
	// Pull the CS Pin Low to select the device
	CS_Select(hnrf);

	HAL_SPI_Transmit(hnrf->hspi, &cmd, 1, 100);

	// Pull the CS Pin High to release the device
	CS_UnSelect(hnrf);
}

void nrf24_reset(NRF24L01* hnrf, uint8_t REG)
{
	if (REG == NRF24L01_STATUS)
	{
		nrf24_writeReg(hnrf, NRF24L01_STATUS, 0x00);
	}

	else if (REG == NRF24L01_FIFO_STATUS)
	{
		nrf24_writeReg(hnrf, NRF24L01_FIFO_STATUS, 0x11);
	}

	else {
	nrf24_writeReg(hnrf, NRF24L01_CONFIG, 0x08);
	nrf24_writeReg(hnrf, NRF24L01_EN_AA, 0x3F);
	nrf24_writeReg(hnrf, NRF24L01_EN_RXADDR, 0x03);
	nrf24_writeReg(hnrf, NRF24L01_SETUP_AW, 0x03);
	nrf24_writeReg(hnrf, NRF24L01_SETUP_RETR, 0x03);
	nrf24_writeReg(hnrf, NRF24L01_RF_CH, 0x02);
	nrf24_writeReg(hnrf, NRF24L01_RF_SETUP, 0x0E);
	nrf24_writeReg(hnrf, NRF24L01_STATUS, 0x00);
	nrf24_writeReg(hnrf, NRF24L01_OBSERVE_TX, 0x00);
	nrf24_writeReg(hnrf, NRF24L01_CD, 0x00);
	uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nrf24_writeRegMulti(hnrf, NRF24L01_RX_ADDR_P0, rx_addr_p0_def, 5);
	uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	nrf24_writeRegMulti(hnrf, NRF24L01_RX_ADDR_P1, rx_addr_p1_def, 5);
	nrf24_writeReg(hnrf, NRF24L01_RX_ADDR_P2, 0xC3);
	nrf24_writeReg(hnrf, NRF24L01_RX_ADDR_P3, 0xC4);
	nrf24_writeReg(hnrf, NRF24L01_RX_ADDR_P4, 0xC5);
	nrf24_writeReg(hnrf, NRF24L01_RX_ADDR_P5, 0xC6);
	uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nrf24_writeRegMulti(hnrf, NRF24L01_TX_ADDR, tx_addr_def, 5);
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P0, 0);
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P1, 0);
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P2, 0);
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P3, 0);
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P4, 0);
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P5, 0);
	nrf24_writeReg(hnrf, NRF24L01_FIFO_STATUS, 0x11);
	nrf24_writeReg(hnrf, NRF24L01_DYNPD, 0);
	nrf24_writeReg(hnrf, NRF24L01_FEATURE, 0);
	}
}

void nrf24_init(NRF24L01* hnrf)
{
	// Disable the chip before configuring the device
	CE_Disable(hnrf);

	nrf24_reset(hnrf, 0);

	nrf24_writeReg(hnrf, NRF24L01_CONFIG, 0);			// Will be configured later
	nrf24_writeReg(hnrf, NRF24L01_EN_AA, 0);			// No Auto ACK
	nrf24_writeReg(hnrf, NRF24L01_EN_RXADDR, 0);		// Not Enabling any pipe right now
	nrf24_writeReg(hnrf, NRF24L01_SETUP_AW, 0x03);		// 5 Bytes for the TX/RX address
	nrf24_writeReg(hnrf, NRF24L01_SETUP_RETR, 0);		// No Retransmission
	nrf24_writeReg(hnrf, NRF24L01_RF_CH, 0);			// Will be setup during TX or RX
	nrf24_writeReg(hnrf, NRF24L01_RF_SETUP, 0x0E);		// Power = 0db, DateRate = 2Mpbs

	// Enable the chip after configuring the device
	CE_Enable(hnrf);
}

// Setup the TX Mode
void nrf24_TxMode(NRF24L01* hnrf, uint8_t* address, uint8_t channel)
{
	// Disable the chip before configuring the device
	CE_Disable(hnrf);

	nrf24_writeReg(hnrf, NRF24L01_RF_CH, channel);				// Select the channel
	nrf24_writeRegMulti(hnrf, NRF24L01_TX_ADDR, address, 5); 	// Write the TX address

	// Power up the device in TX mode
	uint8_t config = nrf24_readReg(hnrf, NRF24L01_CONFIG);
	config = config | (1 << 1);
	nrf24_writeReg(hnrf, NRF24L01_CONFIG, config);

	// Enable the chip after configuring the device
	CE_Enable(hnrf);
}

// Transmit the data
uint8_t nrf24_Transmit(NRF24L01* hnrf, uint8_t* data)
{
	uint8_t cmdToSend = 0;

	//Select device
	CS_Select(hnrf);

	// Payload command
	cmdToSend = NRF24L01_W_TX_PAYLOAD;
	HAL_SPI_Transmit(hnrf->hspi, &cmdToSend, 1, 100);

	// Send the payload
	HAL_SPI_Transmit(hnrf->hspi, data, 32, 1000);

	//Unselect device
	CS_UnSelect(hnrf);

	HAL_Delay(1);

	uint8_t fifoStatus = nrf24_readReg(hnrf, NRF24L01_FIFO_STATUS);
	if((fifoStatus & (1 << 4)) && (!(fifoStatus & (1 << 3))))
	{
		cmdToSend = NRF24L01_FLUSH_TX;
		nrf24_sendCmd(hnrf, cmdToSend);

		nrf24_reset(hnrf, NRF24L01_FIFO_STATUS);

		return 1;
	}

	return 0;
}

// Setup the RX Mode
void nrf24_RxMode(NRF24L01* hnrf, uint8_t* address, uint8_t channel)
{
	// Disable the chip before configuring the device
	CE_Disable(hnrf);

	nrf24_writeReg(hnrf, NRF24L01_RF_CH, channel);					// Select the channel

	// Select data pipe 1
	uint8_t EN_RXADDR = nrf24_readReg(hnrf, NRF24L01_EN_RXADDR);
	EN_RXADDR = EN_RXADDR | (1 << 1);
	nrf24_writeReg(hnrf, NRF24L01_EN_RXADDR, EN_RXADDR);

	nrf24_writeRegMulti(hnrf, NRF24L01_RX_ADDR_P1, address, 5); 	// Write the RX address
	nrf24_writeReg(hnrf, NRF24L01_RX_PW_P1, 32);                    // 32 bytes payload size for pipe 1

	// Power up the device in RX mode
	uint8_t config = nrf24_readReg(hnrf, NRF24L01_CONFIG);
	config = config | (1 << 1) | (1 << 0);
	nrf24_writeReg(hnrf, NRF24L01_CONFIG, config);

	// Enable the chip after configuring the device
	CE_Enable(hnrf);
}

// Wait coming a data
uint8_t nrf24_IsDataAvailable(NRF24L01* hnrf, int pipeNum)
{
	uint8_t status = nrf24_readReg(hnrf, NRF24L01_STATUS);

	if((status & (1 << 6)) && (status & (pipeNum << 1)))
	{
		nrf24_writeReg(hnrf, NRF24L01_STATUS, (1 << 6));
		return 1;
	}

	return 0;
}

// Receiver the data
void nrf24_Receive (NRF24L01* hnrf, uint8_t* data)
{
	uint8_t cmdToSend = 0;

	//Select device
	CS_Select(hnrf);

	// Payload command
	cmdToSend = NRF24L01_R_RX_PAYLOAD;
	HAL_SPI_Transmit(hnrf->hspi, &cmdToSend, 1, 100);

	// Send the payload
	HAL_SPI_Receive(hnrf->hspi, data, 32, 1000);

	//Unselect device
	CS_UnSelect(hnrf);

	HAL_Delay(1);

	cmdToSend = NRF24L01_FLUSH_RX;
	nrf24_sendCmd(hnrf, cmdToSend);
}

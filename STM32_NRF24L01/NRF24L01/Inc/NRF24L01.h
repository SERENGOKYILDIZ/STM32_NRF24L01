/*
 * NRF24L01.h
 *
 *  Created on: Jun 21, 2025
 *      Author: Eren
 */

#ifndef INC_NRF24L01_H_
#define INC_NRF24L01_H_

#include "main.h"

/* Memory Map */
#define NRF24L01_CONFIG 		0X00
#define NRF24L01_EN_AA			0X01
#define NRF24L01_EN_RXADDR 		0X02
#define NRF24L01_SETUP_AW 		0X03
#define NRF24L01_SETUP_RETR		0X04
#define NRF24L01_RF_CH			0X05
#define NRF24L01_RF_SETUP 		0X06
#define NRF24L01_STATUS 		0X07
#define NRF24L01_OBSERVE_TX		0X08
#define NRF24L01_CD		 		0X09
#define NRF24L01_RX_ADDR_P0 	0X0A
#define NRF24L01_RX_ADDR_P1 	0X0B
#define NRF24L01_RX_ADDR_P2 	0X0C
#define NRF24L01_RX_ADDR_P3 	0X0D
#define NRF24L01_RX_ADDR_P4 	0X0E
#define NRF24L01_RX_ADDR_P5 	0X0F
#define NRF24L01_TX_ADDR 		0X10
#define NRF24L01_RX_PW_P0 		0X11
#define NRF24L01_RX_PW_P1 		0X12
#define NRF24L01_RX_PW_P2 		0X13
#define NRF24L01_RX_PW_P3 		0X14
#define NRF24L01_RX_PW_P4 		0X15
#define NRF24L01_RX_PW_P5 		0X16
#define NRF24L01_FIFO_STATUS 	0X17
#define NRF24L01_DYNPD	 		0X1C
#define NRF24L01_FEATURE 		0X1D

/* Instruction Mnemonics */
#define NRF24L01_R_REGISTER			0X00
#define NRF24L01_W_REGISTER			0X20
#define NRF24L01_REGISTER_MASK		0X1F
#define NRF24L01_ACTIVATE			0X50
#define NRF24L01_R_RX_PL_WID		0X60
#define NRF24L01_R_RX_PAYLOAD		0X61
#define NRF24L01_W_TX_PAYLOAD		0XA0
#define NRF24L01_W_ACK_PAYLOAD		0XA8
#define NRF24L01_FLUSH_TX			0XE1
#define NRF24L01_FLUSH_RX			0XE2
#define NRF24L01_REUSE_TX_PL		0XE3
#define NRF24L01_NOP				0XFF


typedef struct{
	GPIO_TypeDef* PORT;
	uint16_t PIN;
}GpioPin;

typedef struct{
	SPI_HandleTypeDef* hspi;
	GpioPin CE;
	GpioPin CS;
}NRF24L01;

void nrf24_init(NRF24L01* hnrf);

void nrf24_TxMode(NRF24L01* hnrf, uint8_t* address, uint8_t channel);
uint8_t nrf24_Transmit(NRF24L01* hnrf,uint8_t* data);

#endif /* INC_NRF24L01_H_ */

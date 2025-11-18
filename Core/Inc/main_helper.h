/*
 * main_helper.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Pc
 */

#ifndef MAIN_HELPER_H
#define MAIN_HELPER_H

#include "stm32f1xx_hal.h"

#define RQST_FOR_DATA 0x0000
#define SPI1_NSS_GPIO GPIOA
#define SPI1_NSS_PIN GPIO_PIN_15

extern SPI_HandleTypeDef hspi1;
extern uint8_t SPI1_Rx_CmdBuff;
extern uint16_t ADC_AvgRslt[];

HAL_StatusTypeDef SPI1_SendData(uint8_t* data, size_t data_size, size_t timeout);

#endif

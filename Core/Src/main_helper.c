/*
 * main_helper.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Pc
 */


#include "stm32f1xx_hal.h"
#include "main_helper.h"

static void process_SPI1_IT();

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi) {
	if (hspi == &hspi1) {
		process_SPI1_IT();
	}
}

static void process_SPI1_IT() {
	HAL_GPIO_WritePin(SPI1_NSS_GPIO, SPI1_NSS_PIN, GPIO_PIN_SET);
}

HAL_StatusTypeDef SPI1_SendData(uint8_t* data, size_t data_size, size_t timeout) {
	HAL_GPIO_WritePin(SPI1_NSS_GPIO, SPI1_NSS_PIN, GPIO_PIN_RESET);

	uint32_t tick_start = HAL_GetTick();
	while(hspi1.State != HAL_SPI_STATE_READY) {
		if (HAL_GetTick() - tick_start > timeout) {
			return HAL_TIMEOUT;
		}
	}

	HAL_SPI_Transmit_DMA(&hspi1, data, data_size);

	return HAL_OK;
}

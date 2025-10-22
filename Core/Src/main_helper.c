/*
 * main_helper.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Pc
 */


#include "stm32f1xx_hal.h"
#include "main_helper.h"

void HAL_DMA_TxCpltCallback(DMA_HandleTypeDef* hdma) {
	if (hdma == hspi1.hdmatx) {
		process_SendRsltsCplt();
	}
}

static void process_SendRsltsCplt() {
	while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY));

	__HAL_SPI_DISABLE(&hspi1);
	CLEAR_BIT(hspi1.Instance->CR2, SPI_CR2_TXDMAEN);

#ifdef __SPI_RX
	HAL_DMA_Abort_IT(hspi1.hdmarx);
	CLEAR_BIT(hspi1.Instance->CR2, SPI_CR2_RXDMAEN);
#endif

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

HAL_StatusTypeDef SPI1_SendData(uint8_t* data, size_t data_size) {
	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY));

#ifdef __SPI_RX
	if (HAL_DMA_Start(hspi1.hdmarx, (uint32_t)&hspi1.Instance->DR, (uint32_t)&SPI1_Rx_CmdBuff, sizeof(SPI1_Rx_CmdBuff))
		!= HAL_OK) {
		return HAL_ERROR;
	}
#endif

	if (HAL_DMA_Start_IT(hspi1.hdmatx, (uint32_t)data, (uint32_t)&hspi1.Instance->DR, data_size)
		!= HAL_OK) {
		return HAL_ERROR;
	}

#ifdef __SPI_RX
	SET_BIT(hspi1.Instance->CR2, SPI_CR2_RXDMAEN);
#endif

	SET_BIT(hspi1.Instance->CR2, SPI_CR2_TXDMAEN);

	__HAL_SPI_ENABLE(&hspi1);

	return HAL_OK;
}

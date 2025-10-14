/*
 * main_helper.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Pc
 */


#include "stm32f1xx_hal.h"
#include "main_helper.h"

extern SPI_HandleTypeDef hspi1;
extern uint16_t spi1_rx_buff;
extern uint16_t ADC_AvgRslt;
extern TIM_HandleTypeDef htim1;

static void process_tim1_it();
static void process_spi1_txrx_it();
static void process_spi1_rx_it();

void wait_for_data_rqst() {
//	while (HAL_UART_Receive(&huart1, &uart1_rx_buff, 1, 1000) != HAL_OK);
//	if (uart1_rx_buff == RQST_FOR_DATA) {
//		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&ADC_AvgRslt, sizeof(ADC_AvgRslt));
//	}

//	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&ADC_AvgRslt, sizeof(ADC_AvgRslt));
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi) {
	if (hspi->Instance == SPI1) {
		process_spi1_rx_it();
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi) {
	if (hspi->Instance == SPI1) {
		process_spi1_txrx_it();
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM1) {
		process_tim1_it();
	}
}

// basically does the same as process_spi1_txrx_it()
static void process_spi1_rx_it() {
	if (spi1_rx_buff == RQST_FOR_DATA) {
		if (TIM1->CR1 & TIM_CR1_CEN) {
			HAL_TIM_Base_Stop_IT(&htim1);
			__HAL_TIM_SET_COUNTER(&htim1, 0);
		}

		HAL_TIM_Base_Start_IT(&htim1);
	}
}

static void process_spi1_txrx_it() {
	if (spi1_rx_buff == RQST_FOR_DATA) {
		if (TIM1->CR1 & TIM_CR1_CEN) {
			HAL_TIM_Base_Stop_IT(&htim1);
			__HAL_TIM_SET_COUNTER(&htim1, 0);
		}

		HAL_TIM_Base_Start_IT(&htim1);
	}
}

static void process_tim1_it() {
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);

	HAL_TIM_Base_Stop_IT(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1, 0);

	HAL_SPI_Receive_DMA(&hspi1, &spi1_rx_buff, sizeof(spi1_rx_buff));
}

/*
 * main_helper.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Pc
 */


#include "stm32f1xx_hal.h"
#include "main_helper.h"

extern UART_HandleTypeDef huart1;
extern uint8_t uart1_rx_buff;
extern uint16_t ADC_AvgRslt;
extern TIM_HandleTypeDef htim1;

void wait_for_data_rqst() {
	while (HAL_UART_Receive(&huart1, &uart1_rx_buff, 1, 1000) != 0) {
	  if (uart1_rx_buff == RQST_FOR_DATA) {
		  HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&ADC_AvgRslt, sizeof(ADC_AvgRslt));
		  break;
	  }
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	HAL_UART_Abort(&huart1);
	HAL_TIM_Base_Start_IT(&htim1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	HAL_TIM_Base_Stop(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&ADC_AvgRslt, sizeof(ADC_AvgRslt));
}

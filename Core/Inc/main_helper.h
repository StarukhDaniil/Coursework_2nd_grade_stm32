/*
 * main_helper.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Pc
 */

#ifndef MAIN_HELPER_H
#define MAIN_HELPER_H

#define RQST_FOR_DATA 0x01

void wait_for_data_rqst();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif

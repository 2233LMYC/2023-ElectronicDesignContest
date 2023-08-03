/*
 * USART.h
 *
 *  Created on: May 2, 2023
 *      Author: leng
 */

#ifndef _USART_2_H_
#define _USART_2_H_

#include "main.h"
#include "string.h"

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

extern uint8_t sti_buff[64];//���������ݴ�����
extern uint8_t uart2_rx_buffer[200];//����1���������ݴ�����
extern uint8_t BUFFER_SIZE;//���ڽ����ַ�����
extern uint8_t rx_len_1;//���յ������ݸ���
extern uint8_t recv_end_flag_1;//����1������ɱ�־λ


void USART_data_processing(void);

#endif /* INC_USART_H_ */

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

extern uint8_t sti_buff[64];//发送数据暂存数组
extern uint8_t uart2_rx_buffer[200];//串口1接收数据暂存数组
extern uint8_t BUFFER_SIZE;//串口接收字符总数
extern uint8_t rx_len_1;//接收到的数据个数
extern uint8_t recv_end_flag_1;//串口1接收完成标志位


void USART_data_processing(void);

#endif /* INC_USART_H_ */

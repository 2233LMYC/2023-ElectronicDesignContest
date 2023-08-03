/*
 *
 *在stm32f1xx_it.c找到串口1的中断服务函数，在中断服务函数中加入以下代码。
//void USART1_IRQHandler(void)
//{
//  * USER CODE BEGIN USART1_IRQn 0 *
//    uint32_t tmp_flag = 0;
//    uint32_t temp;
//    tmp_flag =__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE); //获取IDLE标志位
//    if((tmp_flag != RESET))//idle标志被置位
//    {
//      __HAL_UART_CLEAR_IDLEFLAG(&huart1);//清除标志位
//      HAL_UART_DMAStop(&huart1);
//      temp  =  __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// 获取DMA中未传输的数据个数
//
//      rx_len_1 =  BUFFER_SIZE - temp; //总计数减去未传输的数据个数，得到已经接收的数据个数
//      recv_end_flag_1 = 1;  // 接受完成标志位置1
//    }
//  HAL_UART_Receive_DMA(&huart1,uart1_rx_buffer,BUFFER_SIZE);//重新打开DMA接收
//  * USER CODE END USART1_IRQn 0 *
//  HAL_UART_IRQHandler(&huart1);
//  * USER CODE BEGIN USART1_IRQn 1 *
//
//  * USER CODE END USART1_IRQn 1 *
//}
 *
 *
 *
 *
 *
 * 在main函数中的主循环开始前加入使能语句
 *	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); //使能IDLE中断
 *	HAL_UART_Receive_DMA(&huart1,uart1_rx_buffer,BUFFER_SIZE);
 *
 *
 *
 * */

#include "USART_2.h"
#include "control.h"
#include "stdlib.h"

extern float X_data,Y_data,None;
extern int rect_data[4][2];
extern abc flag;
uint8_t uart2_rx_buffer[200];//串口1接收数据暂存数组
uint8_t BUFFER_SIZE=200;//串口接收字符总数
uint8_t rx_len_1;//接收到的数据个数
uint8_t recv_end_flag_1;//串口1接收完成标志位
uint8_t sti_buff[64];////发送数据暂存数组


/**
 * 函数名:USART_data_processing
 * 描述:处理接收到的串口数据
 * 输入:void
 * 输出:void
 */
void USART_data_processing(void)
{
	if(recv_end_flag_1==1)//串口中断接收标志位
	{
        if(flag.red == 1)
        {
          // 解析字符串，查找"x="和"y="的位置
          const char*px = strstr((const char*)uart2_rx_buffer, "X=");
          const char*py = strstr((const char*)uart2_rx_buffer, "Y=");
          const char*pn = strstr((const char*)uart2_rx_buffer,"None");
          if(pn != NULL)  None = 1;
          else if(px && py)
          {
            None = 0;
            X_data = atoff(px + 2); // +2是为了跳过"x="
            Y_data = atoff(py + 2); // +2是为了跳过"y="
            memset(uart2_rx_buffer, 0, 200);
          }
        }
        else if(flag.rect == 1)
        {
          const char*px1 = strstr((const char*)uart2_rx_buffer, "p1x=");
          const char*py1 = strstr((const char*)uart2_rx_buffer, "p1y=");
          const char*px2 = strstr((const char*)uart2_rx_buffer, "p2x=");
          const char*py2 = strstr((const char*)uart2_rx_buffer, "p2y=");
          const char*px3 = strstr((const char*)uart2_rx_buffer, "p3x=");
          const char*py3 = strstr((const char*)uart2_rx_buffer, "p3y=");
          const char*px4 = strstr((const char*)uart2_rx_buffer, "p4x=");
          const char*py4 = strstr((const char*)uart2_rx_buffer, "p4y=");

          if(px1&&py1&&px2&&py2&&px3&&py3&&px4&&py4)
          {
            rect_data[0][0] = atoi(px1 + 4);
            rect_data[0][1] = atoi(py1 + 4);
            rect_data[1][0] = atoi(px2 + 4);
            rect_data[1][1] = atoi(py2 + 4);

            rect_data[2][0] = atoi(px3 + 4);
            rect_data[2][1] = atoi(py3 + 4);
            rect_data[3][0] = atoi(px4 + 4);
            rect_data[3][1] = atoi(py4 + 4);

            memset(uart2_rx_buffer,0,200);
          }
        }
      }
		recv_end_flag_1 = 0; //标志位置零等待下一次接收
		rx_len_1 = 0;//清除接收到数据的个数

		memset(uart2_rx_buffer,0,sizeof(uart2_rx_buffer)); //初始化接收数组
}


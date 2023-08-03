/*
 *
 *��stm32f1xx_it.c�ҵ�����1���жϷ����������жϷ������м������´��롣
//void USART1_IRQHandler(void)
//{
//  * USER CODE BEGIN USART1_IRQn 0 *
//    uint32_t tmp_flag = 0;
//    uint32_t temp;
//    tmp_flag =__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE); //��ȡIDLE��־λ
//    if((tmp_flag != RESET))//idle��־����λ
//    {
//      __HAL_UART_CLEAR_IDLEFLAG(&huart1);//�����־λ
//      HAL_UART_DMAStop(&huart1);
//      temp  =  __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// ��ȡDMA��δ��������ݸ���
//
//      rx_len_1 =  BUFFER_SIZE - temp; //�ܼ�����ȥδ��������ݸ������õ��Ѿ����յ����ݸ���
//      recv_end_flag_1 = 1;  // ������ɱ�־λ��1
//    }
//  HAL_UART_Receive_DMA(&huart1,uart1_rx_buffer,BUFFER_SIZE);//���´�DMA����
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
 * ��main�����е���ѭ����ʼǰ����ʹ�����
 *	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); //ʹ��IDLE�ж�
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
uint8_t uart2_rx_buffer[200];//����1���������ݴ�����
uint8_t BUFFER_SIZE=200;//���ڽ����ַ�����
uint8_t rx_len_1;//���յ������ݸ���
uint8_t recv_end_flag_1;//����1������ɱ�־λ
uint8_t sti_buff[64];////���������ݴ�����


/**
 * ������:USART_data_processing
 * ����:������յ��Ĵ�������
 * ����:void
 * ���:void
 */
void USART_data_processing(void)
{
	if(recv_end_flag_1==1)//�����жϽ��ձ�־λ
	{
        if(flag.red == 1)
        {
          // �����ַ���������"x="��"y="��λ��
          const char*px = strstr((const char*)uart2_rx_buffer, "X=");
          const char*py = strstr((const char*)uart2_rx_buffer, "Y=");
          const char*pn = strstr((const char*)uart2_rx_buffer,"None");
          if(pn != NULL)  None = 1;
          else if(px && py)
          {
            None = 0;
            X_data = atoff(px + 2); // +2��Ϊ������"x="
            Y_data = atoff(py + 2); // +2��Ϊ������"y="
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
		recv_end_flag_1 = 0; //��־λ����ȴ���һ�ν���
		rx_len_1 = 0;//������յ����ݵĸ���

		memset(uart2_rx_buffer,0,sizeof(uart2_rx_buffer)); //��ʼ����������
}


#ifndef __BSP_USART_REDIR_H
#define __BSP_USART_REDIR_H

#ifdef __cplusplus
extern "C"{
#endif
#include "stm32f4xx_hal.h"
#include <stdio.h>

extern UART_HandleTypeDef* huart;

void BSP_Usart_Init(UART_HandleTypeDef* huart1);
int fputc(int ch, FILE *f);                              // 重定向
int fgetc(FILE *f);
#ifdef __cplusplus
}
#endif


#endif 
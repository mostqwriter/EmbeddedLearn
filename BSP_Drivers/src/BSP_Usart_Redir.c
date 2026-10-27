
#include "BSP_Usart_Redir.h"
UART_HandleTypeDef* huart = NULL;
void BSP_Usart_Init(UART_HandleTypeDef* huart1)
{
	if(huart1 == NULL)
		return;
	huart = huart1;
}

int fputc(int ch, FILE *f)
{
  (void)f;
  uint8_t buffer = (uint8_t)ch;
  if (HAL_UART_Transmit(huart, &buffer, 1, HAL_MAX_DELAY) == HAL_OK)
  {
    return buffer;
  }
  else
    return EOF;
}

int fgetc(FILE *f)
{
  uint8_t data;
  while (1)
  {
    if (HAL_UART_Receive(huart, &data, 1, HAL_MAX_DELAY) == HAL_OK)
    {
      if (data != '\r')
      {
        return data;
      }
    }
    else
    {
      return EOF;
    }
  }
}

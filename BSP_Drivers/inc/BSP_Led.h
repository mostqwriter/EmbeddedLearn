#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
extern "C"{
#endif
#include "stm32f4xx_hal.h"
#include <stdio.h>

typedef enum
{
    LED1 = 0, //PF9
    LED2      //PF10
}LED;


void BSP_Led_On(LED led);
void BSP_Led_Off(LED led);
void BSP_Led_Blink(LED led, uint16_t cnt, uint16_t timeout);


#ifdef __cplusplus
}
#endif

#endif
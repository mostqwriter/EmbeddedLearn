#include "BSP_Led.h"

void BSP_Led_On(LED led)
{
    switch (led)
    {
    case LED1:
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
        break;
    case LED2:
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
        break;
    default:
        break;
    }
}

void BSP_Led_Off(LED led)
{
    switch (led)
    {
    case LED1:
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
        break;
    case LED2:
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
        break;
    default:
        break;
    }
}

void BSP_Led_Blink(LED led, uint16_t cnt, uint16_t timeout)
{
    while (cnt--)
    {
        BSP_Led_On(led);
        HAL_Delay(timeout);
        BSP_Led_Off(led);
        HAL_Delay(timeout);
    }
}
#ifndef __BSP_AT24C02_H
#define __BSP_AT24C02_H

#ifdef __cplusplus
extern "C"{
#endif

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#define AT24C02_PAGE_SIZE 8   //字节
#define AT24C02_PAGE_TOTAL 32 //总页数
#define AT24C02_MEM_SIZE 256  //存储空间
#define AT24C02_ADDRESS 0x50  //器件地址
#define CONFIG_TRAILS 10             //审判次数
#define CONFIG_TIMEOUT 50            //硬件写入时间5ms,适当延长时间

typedef struct  at24c02Init
{
    I2C_HandleTypeDef* hi2c1;
    bool isinit;
}at24c02Init;

extern at24c02Init atinit;
bool BSP_At24c02_Init(I2C_HandleTypeDef *hi2c1);
bool BSP_At24c02_Read(uint8_t memAddress, uint8_t *pData, uint8_t size);
bool BSP_At24c02_Write_Page(uint8_t memAddress, uint8_t *pData, uint8_t size);
bool BSP_At24c02_Write_Pages(uint8_t memAddress, uint8_t *pData, uint8_t size);


#ifdef __cplusplus
}
#endif

#endif
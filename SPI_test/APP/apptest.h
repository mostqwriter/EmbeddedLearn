#ifndef __APPTEST_H
#define __APPTEST_H

#ifdef __cplusplus
extern "C"{
#endif
#include "BSP_W25q128.h"


void Test_BSP_W25q128_Init(SPI_HandleTypeDef* hspi1);
void Test_BSP_W25q128_Read_Date();

#ifdef __cplusplus
}
#endif

#endif
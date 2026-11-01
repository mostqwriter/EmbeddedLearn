#include "apptest.h"

void Test_BSP_W25q128_Init(SPI_HandleTypeDef* hspi1)
{
    printf("---------Test_BSP_W25q128_Init-----------\n");
    BSP_W25q128_Init(hspi1);
}

void Test_BSP_W25q128_Read_Date()
{
    printf("---------Test_BSP_W25q128_Read_Date-----------\n");
    uint8_t buffer[2] = {0xff, 0xff};
    for(int i = 0; i < sizeof(buffer); i++) printf("0x%x ", buffer[i]);
    BSP_W25q128_Read_Date(0, buffer, sizeof(buffer));
    for(int i = 0; i < sizeof(buffer); i++) printf("0x%x ", buffer[i]);
}

void Test_BSP_W25q124_Page_program()
{
    
}
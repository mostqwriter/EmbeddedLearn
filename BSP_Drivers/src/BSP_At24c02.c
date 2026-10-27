#include "BSP_At24c02.h"
#include "BSP_Usart_Redir.h"
at24c02Init atinit;
bool BSP_At24c02_Init(I2C_HandleTypeDef *hi2c1)
{
    uint8_t addr;
    HAL_StatusTypeDef ret;
    printf("---------- I2C总线扫描开始 ----------\r\n");
    for (addr = 0; addr < 128; addr++)
    {
        ret = HAL_I2C_IsDeviceReady(hi2c1, addr << 1, 2, 10);
        if (ret == HAL_OK)
        {
            printf("找到设备地址：0x%02X\r\n", addr);
        }
    }
    printf("---------- I2C总线扫描结束 ----------\r\n");
    if (hi2c1 == NULL)
        return false;
    atinit.hi2c1 = hi2c1;
    if (HAL_I2C_IsDeviceReady(atinit.hi2c1,
                              (AT24C02_ADDRESS << 1),
                              CONFIG_TRAILS,
                              CONFIG_TIMEOUT) == HAL_OK)
    {
        printf("at2402初始化成功！");
        return atinit.isinit = true;
    }
    printf("at2402初始化失败！");
    return atinit.isinit = false;
}

bool BSP_At24c02_Read(uint8_t memAddress, uint8_t *pData, uint8_t size)
{
    if (atinit.isinit == false)
        return false;
    return HAL_I2C_Mem_Read(atinit.hi2c1,
                            (AT24C02_ADDRESS << 1),
                            (uint16_t)memAddress,
                            I2C_MEMADD_SIZE_8BIT,
                            pData,
                            (uint16_t)size,
                            CONFIG_TIMEOUT) == HAL_OK;
}

bool BSP_At24c02_Write_Page(uint8_t memAddress, uint8_t *pData, uint8_t size)
{
    if (atinit.isinit == false)
        return false;
    if (memAddress + size >= AT24C02_MEM_SIZE) // 超出内存边界
    {
        printf("超出内存边界");
        return false;
    }
    if (memAddress + size >
        ((memAddress / AT24C02_PAGE_SIZE + 1) *
         AT24C02_PAGE_SIZE)) // 超出单页限制
    {
        printf("超出单页限制");
        return false;
    }

    HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(atinit.hi2c1,
                                              (AT24C02_ADDRESS << 1),
                                              (uint16_t)memAddress,
                                              I2C_MEMADD_SIZE_8BIT,
                                              pData,
                                              (uint16_t)size,
                                              CONFIG_TIMEOUT);

    if (ret != HAL_OK)
    {
        printf("i2c写入失败！ret=%d\n", ret); // 0=OK, 1=ERROR, 2=BUSY, 3=TIMEOUT
        return false;
    }
    return true;
}

bool BSP_At24c02_Write_Pages(uint8_t memAddress, uint8_t *pData, uint8_t size)
{
    if (atinit.isinit == false)
        return false;
    uint8_t lestSpace = size, curWritePos = memAddress;
    while (lestSpace > 0)
    {
        uint8_t writeSpace = ((AT24C02_PAGE_SIZE - (curWritePos % AT24C02_PAGE_SIZE)) > lestSpace) ? lestSpace : (AT24C02_PAGE_SIZE - (curWritePos % AT24C02_PAGE_SIZE)); // 当前页需要写的空间
        uint8_t *curWriteDataPointer = pData + curWritePos - memAddress;
        if (BSP_At24c02_Write_Page(curWritePos, curWriteDataPointer, writeSpace) == false)
        {
            printf("At24c02页内读取错误！");
            return false;
        }
        curWritePos += writeSpace;
        lestSpace -= writeSpace;
        uint32_t start = HAL_GetTick();

        while (HAL_I2C_IsDeviceReady(atinit.hi2c1,
                                     AT24C02_ADDRESS << 1,
                                     1, 10) != HAL_OK)
        {
            if (HAL_GetTick() - start >= 20)
            {
                printf("EEPROM写入后等待超时，error=0x%lX\r\n",
                       HAL_I2C_GetError(atinit.hi2c1));
                return false;
            }
            HAL_Delay(1);
        }
        // bug
        // if (HAL_I2C_IsDeviceReady(atinit.hi2c1,
        //                           (AT24C02_ADDRESS << 1),
        //                           CONFIG_TRAILS,
        //                           20 * CONFIG_TIMEOUT) != HAL_OK)
        // {
        //     printf("At24c02未准备好！");
        //     return false;
        // }
    }
    return true;
}
#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
extern "C"{
#endif
#include "stm32f4xx_hal.h"
#include "BSP_Usart_Redir.h"
#include <stdio.h>
#include "BSP_Led.h"
#include "BSP_At24c02.h"

typedef struct appInit
{
    uint8_t magic;
    uint8_t version;
    uint8_t led;
    uint8_t cnt;
    uint16_t timeout;
    uint16_t timestart;
}appInit;


#define APP_MAGIC 0x55
#define APP_VERSION 1
#define NEW_CONFIG 1
#define OLD_CONFIG 2
#define MUS_CONVERT(mtime) ((mtime)*1000)
#define STORE_ADDR 1


extern appInit init;

static void printConfig();
bool APP_Init();
void APP_Run();


#ifdef __cplusplus
}
#endif

#endif
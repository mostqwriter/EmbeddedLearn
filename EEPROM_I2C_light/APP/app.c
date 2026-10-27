#include "app.h"

appInit init;

static void printConfig()
{
    printf("magic: %d\n", init.magic);
    printf("version: %d\n", init.version);
    printf("led: %d\n", init.led);
    printf("cnt: %d\n", init.cnt);
    printf("timeout: %d\n", init.timeout);
    printf("timestart: %d\n", init.timestart);
}

bool APP_Init()
{
    init.magic = APP_MAGIC;
    init.version = APP_VERSION;
    printf("请输入你要选择的led灯(0~1)：");
    scanf("%d", (int*)&init.led);
    printf("请输入led灯闪烁次数：(0~255)");
    scanf("%d", (int*)&init.cnt);
    printf("请输入led灯闪烁延时：单位ms");
    scanf("%d", (int*)&init.timeout);
    printf("请输入led灯开始闪烁时间：单位ms");
    scanf("%d", (int*)&init.timestart);
    //将参数写入eeprom
    return (BSP_At24c02_Write_Pages(STORE_ADDR, (uint8_t *)&init, sizeof(init)) == true);
}



void APP_Run()
{
    printf("请选择当前工作模式：1.重新配置参数 2.读取历史参数");

    uint8_t mode = 0;
    scanf("%d", (int*)&mode);

    switch (mode)
    {
    case NEW_CONFIG:
        while(!APP_Init());
        break;
    case OLD_CONFIG:
        //读取at24c02的参数
        BSP_At24c02_Read(STORE_ADDR, (uint8_t *)&init, sizeof(init));
        printConfig();
        break;
    default:
        {
            printf("当前选择错误，请重新选择！");
            return;
        }
    }
    printf("灯%dms后开始闪烁：", init.timeout);
    HAL_Delay(init.timeout);
    BSP_Led_Blink(init.led, init.cnt, init.timeout);
}
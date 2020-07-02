#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <Tasks/TickTask.h>
#include <Tasks/ADCTask.h>
#include <Tasks/LCDTask.h>
#include <DataS.h>
#include <LCD/ULCD.h>
#include <DataSave/Data.h>
#include "gpiohs.h"
#include "gpio.h"

VI VaI;
Now NowData;

void TaskHello(void *pvParameters)
{
    Serial.printf("hello world");
}

void TaskStart()
{
    xTaskCreate(
        TaskHello,
        (const portCHAR *)"Start",
        128,
        NULL,
        2,
        NULL);
    xTaskCreate(
        TaskLCD,
        (const portCHAR *)"LCD",
        128,
        NULL,
        2,
        NULL);

    xTaskCreate(
        TaskADC, (const portCHAR *)"ADC",
        128,
        NULL,
        2,
        NULL);

    xTaskCreate(
        TaskADC, (const portCHAR *)"Tick",
        128,
        NULL,
        2,
        NULL);
}

void setup()
{
    Serial.begin(115200);
    fpioa_set_function(0, FUNC_JTAG_TCLK);
    fpioa_set_function(1, FUNC_JTAG_TDI);
    fpioa_set_function(2, FUNC_JTAG_TMS);
    fpioa_set_function(3, FUNC_JTAG_TDO);
    LCD.begin();
    SaveData.begin();

    NowData.mode = 0;
    NowData.error = 0;
    NowData.open = false;
    NowData.page = 0;

    SaveData.GetData(&VaI);

    VaI.NowI = 0;
    VaI.NowV = 0;

    TaskStart();
    vTaskStartScheduler();
}

void loop()
{
}

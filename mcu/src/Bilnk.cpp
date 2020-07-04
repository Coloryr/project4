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

VI *VaI;
Now *NowData;

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
        TaskADC,
        (const portCHAR *)"ADC",
        128,
        NULL,
        2,
        NULL);

    xTaskCreate(
        TaskTick,
        (const portCHAR *)"Tick",
        128,
        NULL,
        2,
        NULL);
}

void init()
{
    VaI = (VI *)malloc(sizeof(VI));
    NowData = (Now *)malloc(sizeof(Now));

    NowData->mode = 0;
    NowData->error = 0;
    NowData->open = false;
    NowData->page = 0;

    SaveData.GetData(VaI);

    VaI->NowI = 0;
    VaI->NowV = 0;
}

void setup()
{
    Serial.begin(115200);
    LCD.begin();
    SaveData.begin();

    LCD.SetPage(0);

    // init();

    // TaskStart();
    // vTaskStartScheduler();
}

void loop()
{
}

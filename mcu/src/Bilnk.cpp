#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <Tasks/TickTask.h>
#include <Tasks/ADCTask.h>
#include <Tasks/LCDTask.h>
#include <DataS.h>
#include <LCD/ULCD.h>
#include <DataSave/Data.h>

VI VaI;
Now NowData;

void TaskStart()
{
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
    Serial.begin(112500);
    LCD.begin();
    SaveData.begin();
}

void loop()
{
}

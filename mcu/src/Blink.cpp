#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <ALL.h>
#include <Tasks/TickTask.h>
#include <Tasks/ADCTask.h>
#include <Tasks/LCDTask.h>

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
    Save.begin();
}

void loop()
{
}

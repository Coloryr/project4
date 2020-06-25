#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <ALL.h>
#include <Tasks/ADTask.h>
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
        TaskAD, (const portCHAR *)"AD",
        128,
        NULL,
        2,
        NULL);
}

void setup()
{
    Serial.begin(112500);
    LCD.begin();
}

void loop()
{
}

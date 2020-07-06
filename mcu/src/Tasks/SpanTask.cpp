#include <Arduino.h>
#include <Tasks/SpanTask.h>
#include <Key/Key.h>
#include <FreeRTOS.h>
#include <task.h>

void TaskSpan(void *pvParameters)
{
    Serial.println("Task Span");
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        KeyBoard.SpanScan();
        vTaskDelayUntil(&xLastWakeTime, (2 / portTICK_RATE_MS));
    }
}

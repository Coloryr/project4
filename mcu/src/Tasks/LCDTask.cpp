#include <Arduino.h>
#include <Tasks/LCDTask.h>
#include <FreeRTOS.h>
#include <task.h>

void TaskLCD(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
         static portTickType xLastWakeTime;
        const portTickType xFrequency = pdMS_TO_TICKS(10000);

        // 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

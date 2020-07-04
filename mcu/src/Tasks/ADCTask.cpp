#include <Arduino.h>
#include <Tasks/ADCTask.h>
#include <AD/ADC.h>
#include <Bilnk.h>
#include <FreeRTOS.h>
#include <task.h>

void TaskADC(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        static portTickType xLastWakeTime;
        const portTickType xFrequency = pdMS_TO_TICKS(100);

        AD_ADC.getI(&VaI->NowI);
        AD_ADC.getV(&VaI->NowV);

        // 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
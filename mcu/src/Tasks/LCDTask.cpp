#include <Arduino.h>
#include <Tasks/LCDTask.h>
#include <FreeRTOS.h>
#include <task.h>
#include <LCD/ULCD.h>
#include <Bilnk.h>

void TaskLCD(void *pvParameters)
{
    Serial.println("Task LCD");
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        LCD.Tick();
        if (NowData.page == 0)
        {
            LCD.UpDate(VaI);
        }
        // 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同
        vTaskDelayUntil(&xLastWakeTime, (100 / portTICK_RATE_MS));
    }
}

#include <Arduino.h>
#include <Key/Key.h>
#include <FreeRTOS.h>
#include <task.h>
#include <ALL.h>

Key KeyBoard;

/*
 1 2 3 ←
 4 5 6 Clear
 7 8 9 Save
 . 0 确认 Back
*/

Key::Key()
{
    pinMode(KA, OUTPUT);
    pinMode(KB, OUTPUT);
    pinMode(KC, OUTPUT);
    pinMode(KD, OUTPUT);

    pinMode(K1, INPUT_PULLUP);
    pinMode(K2, INPUT_PULLUP);
    pinMode(K3, INPUT_PULLUP);
    pinMode(K4, INPUT_PULLUP);

    pinMode(B1, INPUT_PULLUP);
    pinMode(B2, INPUT_PULLUP);
    pinMode(BA, INPUT_PULLUP);

    digitalWrite(KA, HIGH);
    digitalWrite(KB, HIGH);
    digitalWrite(KC, HIGH);
    digitalWrite(KD, HIGH);
}

void Key::KeyTick()
{
    static portTickType xLastWakeTime;
    const portTickType xFrequency = pdMS_TO_TICKS(10);

    // 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同
    xLastWakeTime = xTaskGetTickCount();
    digitalWrite(KA, LOW);
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Number1;
        return;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number2;
        return;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Number3;
        return;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = Backspace;
        return;
    }
    digitalWrite(KA, HIGH);
    digitalWrite(KB, LOW);
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Number4;
        return;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number5;
        return;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Number6;
        return;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = Clear;
        return;
    }
    digitalWrite(KB, HIGH);
    digitalWrite(KC, LOW);
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Number7;
        return;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number8;
        return;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Number9;
        return;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = SaveKey;
        return;
    }
    digitalWrite(KC, HIGH);
    digitalWrite(KD, LOW);
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Point;
        return;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number0;
        return;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Confirm;
        return;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = Back;
        return;
    }
}

KeyDown Key::GetKey()
{
    return NowKeyDown;
}

void Key::KeyClear()
{
    NowKeyDown = NullKey;
}
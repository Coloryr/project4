#include <Arduino.h>
#include <Key/Key.h>
#include <IO.h>
#include <FreeRTOS.h>
#include <task.h>

Key KeyBoard;

/*
 1 2 3 ←
 4 5 6 Clear
 7 8 9 Save
 . 0 确认 Back
*/
/*
 x x x ON
 x x x OFF
 x x x Menu
 x x Save Set
*/
/*
 L1 L2 L3 x
 S1 S2 S3 x
 x x x x
 x x x Back
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
    digitalWrite(B1, HIGH);
    digitalWrite(B2, HIGH);
    digitalWrite(BA, HIGH);

    NowKeyDown = NullKey;
    SpanDown = NullKey;

    B1_Last = B2_Last = GPIO_PV_HIGH;
}

void Key::KeyScan()
{
    digitalWrite(KA, LOW);
    delayMicroseconds(10);
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
    delayMicroseconds(10);
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
    delayMicroseconds(10);
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
    delayMicroseconds(10);
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

void Key::SpanScan()
{
    int B1_now = digitalRead(B1);
    int B2_now = digitalRead(B2);
    int BA_now = digitalRead(BA);
    if (B1_now != B1_Last)
    {
        if (B1_now == GPIO_PV_HIGH)
        {
            if ((B1_Last == GPIO_PV_HIGH) && (B2_now == GPIO_PV_LOW))
                SpanDown = Next;
            else if ((B1_Last == GPIO_PV_LOW) && (B2_now == GPIO_PV_HIGH))
                SpanDown = Last;
            else if ((B2_Last == B2_now) && (B2_now == GPIO_PV_LOW))
                SpanDown = Next;
            else if ((B2_Last == B2_now) && (B2_now == GPIO_PV_HIGH))
                SpanDown = Last;
        }
        else
        {
            if ((B2_Last == GPIO_PV_HIGH) && (B2_now == GPIO_PV_LOW))
                SpanDown = Last;
            else if ((B2_Last == GPIO_PV_LOW) && (B2_now == GPIO_PV_HIGH))
                SpanDown = Next;
            else if ((B2_Last == B2_now) && (B2_now == GPIO_PV_LOW))
                SpanDown = Last;
            else if ((B2_Last == B2_now) && (B2_now == GPIO_PV_HIGH))
                SpanDown = Next;
        }
        B1_Last = B1_now;
        B2_Last = B2_now;
    }
    else if (BA_now == GPIO_PV_LOW)
    {
        while (BA_now != GPIO_PV_HIGH)
        {
            vTaskDelay(200 / portTICK_RATE_MS);
            BA_now = digitalRead(BA);
        }
        SpanDown = Down;
    }
}

KeyDown Key::GetSpan()
{
    return SpanDown;
}

KeyDown Key::GetKey()
{
    return NowKeyDown;
}

void Key::KeyClear()
{
    NowKeyDown = NullKey;
    SpanDown = NullKey;
}
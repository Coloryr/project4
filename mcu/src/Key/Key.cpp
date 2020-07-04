#include <Arduino.h>
#include <Key/Key.h>
#include <IO.h>

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

    NowKeyDown = NullKey;
}

void Key::Tick()
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

KeyDown Key::GetKey()
{
    return NowKeyDown;
}

void Key::KeyClear()
{
    NowKeyDown = NullKey;
}
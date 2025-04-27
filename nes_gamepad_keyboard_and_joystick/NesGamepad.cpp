#include "NesGamepad.h"

NesGamepad::NesGamepad(int latchPin, int pulsePin, int dataPin, unsigned int delayBeforeReadMicros) : 
  latchPin(latchPin), 
  pulsePin(pulsePin),
  dataPin(dataPin),
  delayBeforeReadMicros(delayBeforeReadMicros) {}

void NesGamepad::init() {
  pinMode(latchPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);
  digitalWrite(latchPin, LOW);
  digitalWrite(pulsePin, LOW);

  pinMode(dataPin, INPUT_PULLUP);
}

void NesGamepad::update() {
  bool btns[8]; 

  digitalWrite(pulsePin, LOW);
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(delayBeforeReadMicros * 2);
  digitalWrite(latchPin, LOW);
  delayMicroseconds(delayBeforeReadMicros);

  for (int i = 0; i < btnsCount; i++) {
    btns[i] = !digitalRead(dataPin);
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(delayBeforeReadMicros);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(delayBeforeReadMicros);
  }

  btnA = btns[0];
  btnB = btns[1];
  btnSelect = btns[2];
  btnStart = btns[3];
  btnUp = btns[4];
  btnDown = btns[5];
  btnLeft = btns[6];
  btnRight = btns[7];
}

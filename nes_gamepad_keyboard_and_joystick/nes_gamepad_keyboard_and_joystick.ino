#include <Keyboard.h>
#include "NesGamepad.h"
#include "ButtonDebounce.h"

NesGamepad gamepad(A0, A1, A2);

unsigned long previousBtnUpdateTime = 0;

ButtonDebounce btnDebouces[gamepad.btnsCount] = {
  {},
  {},
  {},
  {},
  {},
  {},
  {},
  {}
};

const char* btnNames[gamepad.btnsCount] = {
  "A",
  "B",
  "Select",
  "Start",
  "Up",
  "Down",
  "Left",
  "Right"
};

const uint8_t keysKeyboard[gamepad.btnsCount] = {
  'k',
  'j',
  '\\',
  KEY_RETURN,
  'w',
  's',
  'a',
  'd'
};

void setup() {
  Serial.begin(115200);
  gamepad.init();
}

void loop() {
  gamepad.update();
  btnDebouces[0].updateState(gamepad.btnA);
  btnDebouces[1].updateState(gamepad.btnB);
  btnDebouces[2].updateState(gamepad.btnSelect);
  btnDebouces[3].updateState(gamepad.btnStart);
  btnDebouces[4].updateState(gamepad.btnUp);
  btnDebouces[5].updateState(gamepad.btnDown);
  btnDebouces[6].updateState(gamepad.btnLeft);
  btnDebouces[7].updateState(gamepad.btnRight);

  unsigned long currentTime = millis();
  unsigned long longDelayTimeout = 1000;
  for (int i = 0; i < gamepad.btnsCount; i++) {
    if (btnDebouces[i].isBtnPressed) {
      if (currentTime - previousBtnUpdateTime > longDelayTimeout) Serial.println();
      Serial.print("+ "); Serial.print(currentTime - previousBtnUpdateTime); Serial.print(" ms "); Serial.print(btnNames[i]); Serial.println(" pressed");
      previousBtnUpdateTime = currentTime;
    }
    if (btnDebouces[i].isBtnReleased) {
      if (currentTime - previousBtnUpdateTime > longDelayTimeout) Serial.println();
      Serial.print("+ "); Serial.print(currentTime - previousBtnUpdateTime); Serial.print(" ms "); Serial.print(btnNames[i]); Serial.println(" released");
      previousBtnUpdateTime = currentTime;
    }
  }
}

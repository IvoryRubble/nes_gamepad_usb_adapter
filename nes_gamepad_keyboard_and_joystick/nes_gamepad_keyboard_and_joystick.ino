#include <Keyboard.h>
#include "NesGamepad.h"

NesGamepad gamepad(A0, A1, A2);

unsigned long previousBtnUpdateTime = 0;

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
  bool btnsPrevious[gamepad.btnsCount];
  initBtns(btnsPrevious);
  gamepad.update();
  bool btns[gamepad.btnsCount];
  initBtns(btns);

  unsigned long currentTime = millis();
  for (int i = 0; i < gamepad.btnsCount; i++) {
    if (btns[i] && !btnsPrevious[i]) {
      Serial.print("+ "); Serial.print(currentTime - previousBtnUpdateTime); Serial.print(" ms "); Serial.print(btnNames[i]); Serial.println(" pressed");
      previousBtnUpdateTime = currentTime;
    }
    if (!btns[i] && btnsPrevious[i]) {
      Serial.print("+ "); Serial.print(currentTime - previousBtnUpdateTime); Serial.print(" ms "); Serial.print(btnNames[i]); Serial.println(" released");
      previousBtnUpdateTime = currentTime;
    }
  }
}

void initBtns(bool btns[]) {
  btns[0] = gamepad.btnA;
  btns[1] = gamepad.btnB;
  btns[2] = gamepad.btnSelect;
  btns[3] = gamepad.btnStart;
  btns[4] = gamepad.btnUp;
  btns[5] = gamepad.btnDown;
  btns[6] = gamepad.btnLeft;
  btns[7] = gamepad.btnRight;
}

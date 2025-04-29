#include <Keyboard.h>
#include <Joystick.h>
#include "NesGamepad.h"
#include "ButtonDebounce.h"

const int latchPin = A0;
const int pulsePin = A1;
const int dataPin = A2;
const unsigned int delayBeforeReadMicros = 6;
NesGamepad gamepad(latchPin, pulsePin, dataPin, delayBeforeReadMicros);

Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 4, 1, false, false, false, false, false, false, false, false, false, false, false);

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

enum ButtonIndex {
  btnUpIndex = 4,
  btnDownIndex = 5,
  btnLeftIndex = 6,
  btnRightIndex = 7
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

const uint8_t keysJoystick[gamepad.btnsCount] = {
  0,
  1,
  2,
  3,
  0,
  0,
  0,
  0
};

void setup() {
  Serial.begin(115200);
  gamepad.init();
  Keyboard.begin();
  joystick.begin();
  delay(2000);
  Serial.println("Please stand by...");
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

  // for (int i = 0; i < gamepad.btnsCount; i++) {
  //   if (btnDebouces[i].isBtnPressed) {
  //     Keyboard.press(keysKeyboard[i]);
  //   }
  //   if (btnDebouces[i].isBtnReleased) {
  //     Keyboard.release(keysKeyboard[i]);
  //   }
  // }

  for (int i = 0; i < 4; i++) {
    if (btnDebouces[i].isBtnPressed) {
      joystick.pressButton(keysJoystick[i]);
    }
    if (btnDebouces[i].isBtnReleased) {
      joystick.releaseButton(keysJoystick[i]);
    }
  }

  bool isArrowChanged = false;
  for (int i = 4; i < gamepad.btnsCount; i++) {
    isArrowChanged = isArrowChanged || (btnDebouces[i].isBtnPressed || btnDebouces[i].isBtnReleased);
  }
  if (isArrowChanged) {
    if (btnDebouces[btnUpIndex].btnState && btnDebouces[btnRightIndex].btnState) {
      joystick.setHatSwitch(0, 45);
    } else if (btnDebouces[btnRightIndex].btnState && btnDebouces[btnDownIndex].btnState) {
      joystick.setHatSwitch(0, 135);
    } else if (btnDebouces[btnDownIndex].btnState && btnDebouces[btnLeftIndex].btnState) {
      joystick.setHatSwitch(0, 225);
    } else if (btnDebouces[btnLeftIndex].btnState && btnDebouces[btnUpIndex].btnState) {
      joystick.setHatSwitch(0, 315);
    } else if (btnDebouces[btnUpIndex].btnState) {
      joystick.setHatSwitch(0, 0);
    } else if (btnDebouces[btnRightIndex].btnState) {
      joystick.setHatSwitch(0, 90);
    } else if (btnDebouces[btnDownIndex].btnState) {
      joystick.setHatSwitch(0, 180);
    } else if (btnDebouces[btnLeftIndex].btnState) {
      joystick.setHatSwitch(0, 270);
    } else {
      joystick.setHatSwitch(0, -1);
    }
  }

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

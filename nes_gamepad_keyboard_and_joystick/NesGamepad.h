#ifndef NesGamepad_h
#define NesGamepad_h

#include <Arduino.h>

class NesGamepad {
  public:
    NesGamepad(int latchPin, int pulsePin, int dataPin, unsigned int delayBeforeReadMicros = 6);
    void init();
    void update();

    bool btnA = false;
    bool btnB = false;
    bool btnSelect = false;
    bool btnStart = false;
    bool btnUp = false;
    bool btnDown = false;
    bool btnLeft = false;
    bool btnRight = false;

    static const int btnsCount = 8;

  private:
    int latchPin;
    int pulsePin;
    int dataPin;
    unsigned int delayBeforeReadMicros;
};

#endif
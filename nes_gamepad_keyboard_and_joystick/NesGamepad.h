//
// NesGamepad.h
//
// Author:
//       Yaroslav Metelev <yaroslav.metelev@outlook.com>
//
// Copyright (c) 2025 Yaroslav Metelev <https://github.com/IvoryRubble>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

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
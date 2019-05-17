/*
  Button.h - Arduino library for a button
  Created by Vektor Sepesi, 2019
  MIT license
*/

#ifndef BUTTON_h
#define BUTTON_h

#include "Arduino.h"

#define DEBOUNCE 20 // 20ms
#define DOUBLE_CLICK 400 // max 0.4 sec between presses
#define SHORT_HOLD 1000 // at least 1 sec, max LONG_HOLD
#define LONG_HOLD 3000 // at least 3 sec

class BUTTON {
  public:
    BUTTON(uint8_t pin);
    uint8_t clickType();

  private:
    uint8_t _pin;
    bool _buttonState;
    bool _buttonStatePrev;
    bool _buttonChange;
    bool _buttonPressed;
    bool _buttonReleased;
    uint32_t _tButtonChange;
    uint32_t _tButtonPress;
    uint32_t _tButtonPressPrev;
    uint32_t _tButtonRelease;
};

#endif
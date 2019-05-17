/*
  Button.cpp - Arduino library for a button
  Created by Vektor Sepesi, 2019
  MIT license
*/

#include "Button.h"

/*
  Constructor, initializes the button connected to the specified digital pin.
*/
BUTTON::BUTTON(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
  _buttonState = true; // true = released
  _buttonStatePrev = true;
  _buttonChange = false;
  _buttonPressed = false;
  _buttonReleased = false;
  _tButtonChange = 0;
  _tButtonPress = 0;
  _tButtonPressPrev = 0;
  _tButtonRelease = 0;  
}

/*
  Returns button's click type
  0 = No click
  1 = Single click
  2 = Double click
  3 = Short hold
  4 = Long hold
*/
uint8_t BUTTON::clickType() {
  uint8_t clickType = 0;
  _buttonStatePrev = _buttonState;
  _buttonState = digitalRead(_pin);

  // Detect button change
  if (_buttonState != _buttonStatePrev) {
    _buttonChange = true;
    _tButtonChange = millis();
  }

  // Debounce and determine whether the button was pressed or released
  if (_buttonChange == true && (millis() - _tButtonChange) > DEBOUNCE) {
    _buttonChange = false;
    if (_buttonState == false) {
      _buttonPressed = true;
      _buttonReleased = false;
      _tButtonPressPrev = _tButtonPress;
      _tButtonPress = millis();
    } else {
      _buttonReleased = true;
      _tButtonRelease = millis();
    }
  }

  // Distinguish between single and double click, short and long hold
  if (_buttonPressed == true && _buttonReleased == true) {
    if ((_tButtonPress - _tButtonPressPrev) < DOUBLE_CLICK) {
      clickType = 2; // Double click
      _buttonPressed = false;
      _buttonReleased = false;
    }
    if ((millis() - _tButtonPress) > DOUBLE_CLICK) {
      if ((_tButtonRelease - _tButtonPress) > LONG_HOLD) {
        clickType = 4; // Long hold
      } else if ((_tButtonRelease - _tButtonPress) > SHORT_HOLD) {
        clickType = 3; // Short hold
      } else {
        clickType = 1; // Single click
      }
      _buttonPressed = false;
      _buttonReleased = false;
    }
  }
  return clickType;
}
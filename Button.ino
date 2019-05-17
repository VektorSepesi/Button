/*
  Example sketch for the Button library.
  Created by Vektor Sepesi, 2019
  MIT license
*/

#include "Button.h"

BUTTON button(2); // Button connected to D2 pin.

void setup() {
  Serial.begin(9600);
}

void loop() {
  handleButton(button.clickType());
}

void handleButton(uint8_t clickType) {
  switch (clickType) {
    case 1:
      Serial.println("Single click");
      break;
    case 2:
      Serial.println("Double click");
      break;
    case 3:
      Serial.println("Short hold");
      break;
    case 4:
      Serial.println("Long hold");
      break;
    default:
      break;
  }
}

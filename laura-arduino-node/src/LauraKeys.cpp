#include "LauraKeys.hpp"

LauraKeysClass::LauraKeysClass()
: _rowPins { A1, A2 }
, _colPins { A3, A4, A5 }
, _keys {{ 1, 2, 3 }, { 4, 5, 6 }}
, _numRows {2}
, _numCols {3}
, _keypad (makeKeymap(_keys), _rowPins, _colPins, _numRows, _numCols)
{}

void LauraKeysClass::init() {
  _keypad.begin();
}

void LauraKeysClass::reinit() {
  for (int i = 0; i < _numCols; i++) {
    pinMode(_colPins[i], OUTPUT);
    digitalWrite(_colPins[i], HIGH);
  }

  for (int i = 0; i < _numRows; i++) {
    pinMode(_rowPins[i], INPUT_PULLUP);
  }

  _keypad.clear();
}

void LauraKeysClass::attachWakeupInterrupts() {
  for (int i = 0; i < _numCols; i++) {
    pinMode(_colPins[i], OUTPUT);
    digitalWrite(_colPins[i], LOW);
  }

  for (int i = 0; i < _numRows; i++) {
    pinMode(_rowPins[i], INPUT_PULLUP);
    LowPower.attachInterruptWakeup(digitalPinToInterrupt(_rowPins[i]), []{}, FALLING);
  }
}

void LauraKeysClass::detachWakeupInterrupts() {
  for (int i = 0; i < _numRows; i++) {
    detachInterrupt(digitalPinToInterrupt(_rowPins[i]));
  }
}

KeyEvent LauraKeysClass::getKey(bool waitForLongPress) {
  struct KeyEvent found = { 0, false };

  auto startTime = millis();
  while (!found.code && ((millis() - startTime) < 100)) {
    _keypad.tick();

    if (_keypad.available()) {
      keypadEvent e = _keypad.read();

      if (e.bit.EVENT = KEY_JUST_PRESSED) {
        found.code = e.bit.KEY;
        break;
      }
    }
    delay(20);
  }

  if (waitForLongPress) {
    startTime = millis();
    _keypad.tick();
    while (_keypad.isPressed(found.code)) {
      if (millis() - startTime > 500) {
        found.longPress = true;
        break;
      }

      delay(20);
      _keypad.tick();
    }
  }

  return found;
}

void LauraKeysClass::waitUntilReleased(char code) {
  _keypad.tick();
  while (_keypad.isPressed(code)) {
    delay(20);
    _keypad.tick();
  }
}

LauraKeysClass LauraKeys;

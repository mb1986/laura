#ifndef _LAURA_KEYS_HPP_
#define _LAURA_KEYS_HPP_

#include <Adafruit_Keypad.h>
#include <ArduinoLowPower.h>

struct KeyEvent {
  char code;
  bool longPress;
};

class LauraKeysClass {

public:
  LauraKeysClass();

  void init();
  void reinit();

  KeyEvent getKey(bool waitForLongPress = true);
  void waitUntilReleased(char code);

  void attachWakeupInterrupts();
  void detachWakeupInterrupts();

private:
  int _numRows;
  int _numCols;
  byte _rowPins[2];
  byte _colPins[3];
  char _keys[2][3];
  Adafruit_Keypad _keypad;
};

extern LauraKeysClass LauraKeys;

#endif

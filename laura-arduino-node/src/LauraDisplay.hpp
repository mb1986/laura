#ifndef _LAURA_DISPLAY_HPP_
#define _LAURA_DISPLAY_HPP_

#include <functional>

// #include <GFX.h>
#include <GxEPD2_BW.h>

#include "LauraMenu.hpp"

class LauraDisplayClass {

public:
  void init();
  void clear(uint16_t color = GxEPD_WHITE);

  void drawHeader(int rssi, float snr, long cfo);
  void drawMenu();
  void update(bool partial = false);

  void hibernate();
  void powerOff();
};

extern LauraDisplayClass LauraDisplay;

#endif

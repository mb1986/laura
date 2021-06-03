#ifndef _LAURA_DISPLAY_HPP_
#define _LAURA_DISPLAY_HPP_

#include <functional>

// #include <GFX.h>
#include <GxEPD2_BW.h>

#include "LauraMenu.hpp"

class LauraDisplayClass {

public:
  void init();

  void setFullWindow();

  void setHeaderWindow();
  void drawHeader(int rssi, float snr, long cfo);

  void setMenuWindow();
  void drawMenu();

  void draw(std::function<void(void)> drawFunc);

  void hibernate();

private:
  void firstPage();
  bool nextPage();
};

extern LauraDisplayClass LauraDisplay;

#endif

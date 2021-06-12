#include "LauraDisplay.hpp"
#include "GxEPD2_display_selection_new_style.h"

// fonts
#include "pixelated8pt7b.h"

#define BUFFER_SIZE   256

#define HEADER_HEIGHT 8
#define HEADER_STRING "RSSI: % 4d dB    SNR: % 6.2f dB    CFO: % 6ld Hz"

#define MENU_HEIGHT   16
#define MENU_WIDTH    47
#define MENU_GAP      2
#define MENU_POS_Y    128 - MENU_HEIGHT - 1

char buffer[BUFFER_SIZE];

void LauraDisplayClass::init() {
  display.init();
  display.setRotation(3);
  display.setFont(nullptr);
}

void LauraDisplayClass::clear(uint16_t color) {
  display.setFullWindow();
  display.fillScreen(color);
}

void LauraDisplayClass::drawHeader(int rssi, float snr, long cfo) {

  snprintf(buffer, BUFFER_SIZE, HEADER_STRING, rssi, snr, cfo);

  display.setFullWindow();
  display.fillRect(0, 0, display.width(), HEADER_HEIGHT, GxEPD_WHITE);

  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.print(buffer);
}

void LauraDisplayClass::drawMenu() {

  MenuBar *menu = LauraMenu.menu();

  display.setFullWindow();
  display.fillRect(0, MENU_POS_Y, display.width(), MENU_HEIGHT, GxEPD_WHITE);

  display.setFont(&pixelated8pt7b);
  display.setTextColor(GxEPD_WHITE);

  int x = 0;

  for (int i = 0; i < 6; i++) {

    MenuItem *item = &menu->items[i];

    x += MENU_GAP;

    // if label is not nullptr then draw menu rect
    if (item->label) {
      display.fillRect(x, MENU_POS_Y, MENU_WIDTH, MENU_HEIGHT, GxEPD_BLACK);

      // if label is not empty string then draw menu text
      if (item->label[0]) {

        char *label = item->label;

        if (item->param) {
          snprintf(buffer, BUFFER_SIZE, label, *item->param);
          label = buffer;
        }

        int16_t tbx, tby;
        uint16_t tbw, tbh;
        display.getTextBounds(label, 0, 0, &tbx, &tby, &tbw, &tbh);

        uint16_t tx = ((MENU_WIDTH - tbw) / 2) - tbx + x;
        // uint16_t ty = ((MENU_HEIGHT - tbh) / 2) - tby + MENU_POS_Y;

        display.setCursor(tx, MENU_POS_Y + 12);
        // display.setCursor(tx, ty);
        display.print(label);
      }
    }

    x += MENU_WIDTH;

  }

  display.setFont(nullptr);
  display.setTextColor(GxEPD_BLACK);
}

void LauraDisplayClass::update(bool partial) {
  display.display(partial);
}

void LauraDisplayClass::hibernate() {
  display.hibernate();
}

void LauraDisplayClass::powerOff() {
  display.powerOff();
}

LauraDisplayClass LauraDisplay;

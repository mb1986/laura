#ifndef _LAURA_MENU_HPP_
#define _LAURA_MENU_HPP_

#include <functional>

#define MENU_BARS_NO  8
#define MENU_ITEMS_NO 6

typedef std::function<void(char)> AlphaHandler;

enum MenuParam {
  LORA_SF = 0,
  FINAL_MenuParam_ENTRY,
};

struct MenuItem {
  char *label;
  struct MenuBar *next;
  std::function<void(void)> handler;
  char **param;
};

struct MenuBar {
  struct MenuItem items[MENU_ITEMS_NO];
};

class LauraMenuClass {
public:
  LauraMenuClass();

  void select(char keyNo);

  void onSelectAlpha(AlphaHandler alphaHandler);

  void setParam(MenuParam p, char* value);

  MenuBar* menu();

private:
  char *_params[FINAL_MenuParam_ENTRY];

private:
  AlphaHandler _alphaHandler;
  void _handleAlpha(char c);

private:
  MenuBar *_menu;
  MenuBar _menuDef[MENU_BARS_NO];
};

extern LauraMenuClass LauraMenu;

#endif

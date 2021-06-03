#ifndef _LAURA_MENU_HPP_
#define _LAURA_MENU_HPP_

#include <functional>

#define MENU_BARS_NO  7
#define MENU_ITEMS_NO 6

typedef std::function<void(void)> Handle;
typedef std::function<void(char)> AlphaHandle;

struct MenuItem {
  char *label;
  struct MenuBar *next;
  Handle handle;
};

struct MenuBar {
  struct MenuItem items[MENU_ITEMS_NO];
};

class LauraMenuClass {
public:
  LauraMenuClass();

  void select(char keyNo);

  void registerAlphaHandler(AlphaHandle alphaHandler);

  MenuBar* menu();

private:
  AlphaHandle _alphaHandler;
  void _handleAlpha(char c);

private:
  MenuBar *_menu;
  MenuBar _menuDef[MENU_BARS_NO];
};

extern LauraMenuClass LauraMenu;

#endif

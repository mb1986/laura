#include "LauraMenu.hpp"

LauraMenuClass::LauraMenuClass()
: _menuDef {
  MenuBar { // 0
    MenuItem {"ABCDE", &_menuDef[1]},
    MenuItem {"FGHI", &_menuDef[2]},
    MenuItem {"JKLM", &_menuDef[3]},
    MenuItem {"NOPQ", &_menuDef[4]},
    MenuItem {"RSTUV", &_menuDef[5]},
    MenuItem {"WXYZ", &_menuDef[6]},
  },
  MenuBar { // 1
    MenuItem {"A", &_menuDef[0], [&]{ _handleAlpha('A'); }},
    MenuItem {"B", &_menuDef[0], [&]{ _handleAlpha('B'); }},
    MenuItem {"C", &_menuDef[0], [&]{ _handleAlpha('C'); }},
    MenuItem {"D", &_menuDef[0], [&]{ _handleAlpha('D'); }},
    MenuItem {"E", &_menuDef[0], [&]{ _handleAlpha('E'); }},
    MenuItem {""},
  },
  MenuBar { // 2
    MenuItem {"F", &_menuDef[0], [&]{ _handleAlpha('F'); }},
    MenuItem {"G", &_menuDef[0], [&]{ _handleAlpha('G'); }},
    MenuItem {"H", &_menuDef[0], [&]{ _handleAlpha('H'); }},
    MenuItem {"I", &_menuDef[0], [&]{ _handleAlpha('I'); }},
    MenuItem {""},
    MenuItem {""},
  },
  MenuBar { // 3
    MenuItem {"J", &_menuDef[0], [&]{ _handleAlpha('J'); }},
    MenuItem {"K", &_menuDef[0], [&]{ _handleAlpha('K'); }},
    MenuItem {"L", &_menuDef[0], [&]{ _handleAlpha('L'); }},
    MenuItem {"M", &_menuDef[0], [&]{ _handleAlpha('M'); }},
    MenuItem {""},
    MenuItem {""},
  },
  MenuBar { // 4
    MenuItem {"N", &_menuDef[0], [&]{ _handleAlpha('N'); }},
    MenuItem {"O", &_menuDef[0], [&]{ _handleAlpha('O'); }},
    MenuItem {"P", &_menuDef[0], [&]{ _handleAlpha('P'); }},
    MenuItem {"Q", &_menuDef[0], [&]{ _handleAlpha('Q'); }},
    MenuItem {""},
    MenuItem {""},
  },
  MenuBar { // 5
    MenuItem {"R", &_menuDef[0], [&]{ _handleAlpha('R'); }},
    MenuItem {"S", &_menuDef[0], [&]{ _handleAlpha('S'); }},
    MenuItem {"T", &_menuDef[0], [&]{ _handleAlpha('T'); }},
    MenuItem {"U", &_menuDef[0], [&]{ _handleAlpha('U'); }},
    MenuItem {"V", &_menuDef[0], [&]{ _handleAlpha('V'); }},
    MenuItem {""},
  },
  MenuBar { // 6
    MenuItem {"W", &_menuDef[0], [&]{ _handleAlpha('W'); }},
    MenuItem {"X", &_menuDef[0], [&]{ _handleAlpha('X'); }},
    MenuItem {"Y", &_menuDef[0], [&]{ _handleAlpha('Y'); }},
    MenuItem {"Z", &_menuDef[0], [&]{ _handleAlpha('Z'); }},
    MenuItem {""},
    MenuItem {""},
  },
}
, _menu { &_menuDef[0] }
{}

void LauraMenuClass::select(char keyNo) {
  if (keyNo < 1 && keyNo > MENU_ITEMS_NO) return;

  MenuItem* selectedItem = &_menu->items[keyNo - 1];

  if (selectedItem->handle) {
    selectedItem->handle();
  }

  if (selectedItem->next) {
    _menu = selectedItem->next;
  }
}

MenuBar* LauraMenuClass::menu() {
  return _menu;
}

void LauraMenuClass::registerAlphaHandler(AlphaHandle alphaHandler) {
  _alphaHandler = alphaHandler;
}

void LauraMenuClass::_handleAlpha(char c) {
  if (_alphaHandler) {
    _alphaHandler(c);
  }
}

LauraMenuClass LauraMenu;
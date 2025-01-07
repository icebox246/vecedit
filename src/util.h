#pragma once

#include <raylib.h>

constexpr static inline bool isOnMaxOS() {
#ifdef __APPLE__
  return true;
#else
  return false;
#endif
}

constexpr static inline int keyboardShortcutMod() {
#ifdef __APPLE__
  return KEY_LEFT_SUPER;
#else
  return KEY_LEFT_CONTROL;
#endif
}

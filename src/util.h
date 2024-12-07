#pragma once

constexpr static inline bool isOnMaxOS() {
#ifdef __APPLE__
  return true;
#else
  return false;
#endif
}

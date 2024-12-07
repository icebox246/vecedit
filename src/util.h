#pragma once

constexpr static inline bool isOnMaxOS() {
#ifdef __APPLE__
  return true;
#elif
  return false;
#endif
}

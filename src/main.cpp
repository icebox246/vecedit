#include <iostream>
#include "ui/AppUi.h"

#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

int main() {
  std::cout << "Hello, VecEdit!" << std::endl;

  InitWindow(1000, 800, "VecEdit");

  {
    ui::AppUi appUi;

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    bool firstFrame = true;

    while (!WindowShouldClose()) {
      BeginDrawing();

      ClearBackground(RAYWHITE);

      if (IsWindowResized() || firstFrame)
        appUi.setRect({
            0,
            0,
            static_cast<float>(GetScreenWidth()),
            static_cast<float>(GetScreenHeight()),
        });

      appUi.update();

      EndDrawing();

      firstFrame = false;
    }
  }

  CloseWindow();

  return 0;
}

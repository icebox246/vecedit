#pragma once

#include <memory>

#include "DocumentTabs.h"
#include "Editor.h"
#include "KeyboardShortcut.h"
#include "Toolbar.h"

namespace ui {

class AppUi : public Widget {
  std::shared_ptr<DocumentTabs> tabBar;
  std::shared_ptr<Toolbar> toolbar;
  std::shared_ptr<Editor> editor;
  std::vector<KeyboardShortcut> shortcuts;

 public:
  AppUi();

  void update() override;
  void setRect(const Rectangle& rect) override;

 private:
  void addShortcut(std::shared_ptr<strategy::Strategy<>> strat,
                   int key,
                   int mod = 0);
};

}  // namespace ui

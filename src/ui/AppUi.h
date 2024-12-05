#pragma once

#include <memory>

#include "DocumentTabs.h"
#include "Editor.h"
#include "Toolbar.h"

namespace ui {

class AppUi : public Widget {
  std::shared_ptr<DocumentTabs> tabBar;
  std::shared_ptr<Toolbar> toolbar;
  std::shared_ptr<Editor> editor;

 public:
  AppUi();

  void update() override;
  void setRect(const Rectangle& rect) override;
};

}  // namespace ui

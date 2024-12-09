#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "Widget.h"
#include "strategy/Strategy.h"

namespace ui {

class DocumentTabs : public Widget {
  std::filesystem::path openedFilePath;
  std::shared_ptr<strategy::Strategy<std::filesystem::path>> openStrategy;

 public:
  ~DocumentTabs() override = default;

  void update() override;

  void setOpenedFile(std::string newName);

  void setOpenStrategy(
      std::shared_ptr<strategy::Strategy<std::filesystem::path>> strategy);
};

}  // namespace ui

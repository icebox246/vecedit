#pragma once

#include <filesystem>
#include <memory>

#include "../Document.h"
#include "Widget.h"
#include "strategy/Strategy.h"

namespace ui {

class DocumentTabs : public Widget {
  std::shared_ptr<Document> openedDocument;
  std::shared_ptr<strategy::Strategy<std::shared_ptr<Document>>> openStrategy;

 public:
  ~DocumentTabs() override = default;

  void update() override;

  void setOpenedFile(std::filesystem::path newName);

  void setOpenStrategy(
      std::shared_ptr<strategy::Strategy<std::shared_ptr<Document>>> strategy);
};

}  // namespace ui

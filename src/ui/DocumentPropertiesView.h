#pragma once

#include <memory>

#include "../Document.h"
#include "Widget.h"
#include "strategy/Strategy.h"

namespace ui {

class DocumentPropertiesView : public Widget {
  std::shared_ptr<Document> doc;

  bool selectedFilename;
  bool selectedWidth;
  bool selectedHeight;

  char filenameText[128], widthText[32], heightText[32];

  std::shared_ptr<strategy::Strategy<>> doneStrategy;

 public:
  void update() override;

  void setDocumentAndUpdateInfo(std::shared_ptr<Document>);

  void setDoneStrategy(std::shared_ptr<strategy::Strategy<>> strat) {
    doneStrategy = std::move(strat);
  }
  void updateFilenameField(Rectangle& subRect);
  void updateDimensionFields(Rectangle& subRect);
  void updateApplyButton(Rectangle& subRect);
};

}  // namespace ui

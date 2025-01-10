#include "DocumentPropertiesView.h"

#include <raygui.h>
#include <cstring>
#include <format>

#include "../ui/command/ChangeDocumentProperties.h"

namespace {
constexpr auto ElementHeight = 20;
}

void ui::DocumentPropertiesView::update() {
  auto subRect = Rectangle{rect.x, rect.y, rect.width, ElementHeight};

  updateFilenameField(subRect);
  updateDimensionFields(subRect);
  updateApplyButton(subRect);
}

void ui::DocumentPropertiesView::setDocumentAndUpdateInfo(
    std::shared_ptr<Document> newDoc) {
  doc = std::move(newDoc);

  std::strcpy(filenameText, doc->getFilePath().c_str());

  auto dims = doc->getDimensions();

  auto ws = std::format("{:.0f}", dims.x);
  std::strcpy(widthText, ws.c_str());

  auto hs = std::format("{:.0f}", dims.y);
  std::strcpy(heightText, hs.c_str());
}
void ui::DocumentPropertiesView::updateFilenameField(Rectangle& subRect) {
  {
    GuiLabel(subRect, "Filename");
    subRect.y += ElementHeight;

    if (GuiTextBox(subRect, filenameText, sizeof(filenameText),
                   selectedFilename)) {
      selectedFilename = !selectedFilename;
    }
    subRect.y += ElementHeight;
  }
}
void ui::DocumentPropertiesView::updateDimensionFields(Rectangle& subRect) {
  {
    GuiLabel(subRect, "Width");
    subRect.y += ElementHeight;

    if (GuiTextBox(subRect, widthText, sizeof(widthText), selectedWidth)) {
      selectedWidth = !selectedWidth;
    }
    subRect.y += ElementHeight;
  }

  {
    GuiLabel(subRect, "Height");
    subRect.y += ElementHeight;

    if (GuiTextBox(subRect, heightText, sizeof(heightText), selectedHeight)) {
      selectedHeight = !selectedHeight;
    }
    subRect.y += ElementHeight;
  }
}
void ui::DocumentPropertiesView::updateApplyButton(Rectangle& subRect) {
  {
    subRect.y += ElementHeight;

    if (GuiButton(subRect, "Apply")) {
      if (doneStrategy)
        doneStrategy->execute();

      std::filesystem::path newPath(filenameText);
      Vector2 newDims{static_cast<float>(atof(widthText)),
                      static_cast<float>(atof(heightText))};

      doc->getCommandManager().addAndExecCommand(
          std::make_shared<command::ChangeDocumentPropertiesCommand>(
              doc, newPath, newDims));
    }
  }
}

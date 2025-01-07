#include "FigurePropertiesPanel.h"

#include <raygui.h>
#include <cmath>
#include <format>

void ui::FigurePropertiesPanel::update() {
  GuiPanel(rect, "Figure properties");
  if (!editedFig) {
    auto r = Rectangle{rect.x + 10, rect.y + 20, rect.width - 20, 40};

    GuiLabel(r, GuiIconText(ICON_CURSOR_CLASSIC, "Select a figure"));
    return;
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    startFigProps =
        command::ChangeFigurePropsCommand::FigureProps::makePropsFromFig(
            *editedFig);
  }

  float yOffset = rect.y + 30;

  {
    Color c;

    switch (colorEditMode) {
      case ColorMode::Fill:
        c = editedFig->getFill();
        break;
      case ColorMode::Stroke:
        c = editedFig->getStroke();
        break;
    }
    auto oldC = c;

    GuiLabel(Rectangle{rect.x + 10, yOffset, rect.width - 40, 20}, "Color");
    auto colorPickRect =
        Rectangle{rect.x + 10, yOffset + 20, rect.width - 40, rect.width - 20};
    GuiColorPicker(colorPickRect, "Color", &c);

    yOffset += rect.width + 10;
    float alphaF = c.a / 255.f;
    GuiColorBarAlpha(Rectangle{rect.x + 10, yOffset, (rect.width - 40), 20},
                     "Alpha", &alphaF);
    c.a = alphaF * 255;

    if (!ColorIsEqual(c, oldC)) {
      switch (colorEditMode) {
        case ColorMode::Fill:
          editedFig->setFill(c);
          break;
        case ColorMode::Stroke:
          editedFig->setStroke(c);
          break;
      }

      uncommitedChanges = true;
    }
  }

  yOffset += 30;
  {
    int selection = (int)colorEditMode;
    GuiToggleGroup(Rectangle{rect.x + 10, yOffset, (rect.width - 40) / 2, 20},
                   "Fill;Stroke", (int*)&selection);

    colorEditMode = (ColorMode)(selection);
  }

  yOffset += 30;
  {
    float f = editedFig->getStrokeWeight();
    auto oldF = f;

    GuiLabel(Rectangle{rect.x + 10, yOffset, rect.width - 40, 20},
             "Stroke weight");
    GuiSlider(Rectangle{rect.x + 10, yOffset + 20, rect.width - 40, 20}, "", "",
              &f, 0, 32);

    f = std::floorf(f / 0.5) * 0.5;

    GuiLabel(Rectangle{rect.x + rect.width - 25, yOffset + 20, 25, 20},
             std::format("{:.1f}", f).c_str());

    if (f != oldF) {
      editedFig->setStrokeWeight(f);
      uncommitedChanges = true;
    }
  }

  if (uncommitedChanges && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    registerChangePropsCommand();
    uncommitedChanges = false;
  }
}

void ui::FigurePropertiesPanel::setDocument(std::shared_ptr<Document> doc) {
  this->doc = std::move(doc);
}

void ui::FigurePropertiesPanel::setFigure(
    std::shared_ptr<figure::Figure> newFig) {
  editedFig = std::move(newFig);
  uncommitedChanges = false;
}

void ui::FigurePropertiesPanel::registerChangePropsCommand() {
  TraceLog(LOG_INFO, "Registering change props command");
  assert(doc);
  auto endProps =
      command::ChangeFigurePropsCommand::FigureProps::makePropsFromFig(
          *editedFig);

  if (startFigProps == endProps)
    return;

  doc->getCommandManager().addCommand(
      std::make_shared<command::ChangeFigurePropsCommand>(
          editedFig, startFigProps, endProps));
}

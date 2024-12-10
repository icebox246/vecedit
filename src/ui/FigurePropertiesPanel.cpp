#include "FigurePropertiesPanel.h"

#include <raygui.h>
#include <cmath>
#include <format>

void ui::FigurePropertiesPanel::update() {
  GuiPanel(rect, "Properties");
  if (!editedFig) {
    auto r = Rectangle{rect.x + 10, rect.y + 20, rect.width - 20, 40};

    GuiLabel(r, GuiIconText(ICON_CURSOR_CLASSIC, "Select a figure"));
    return;
  }

  {
    float yOffset = rect.y + 30;

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

    if (!ColorIsEqual(c, oldC)) {
      // TODO: register a command on mouse up
      switch (colorEditMode) {
        case ColorMode::Fill:
          editedFig->setFill(c);
          break;
        case ColorMode::Stroke:
          editedFig->setStroke(c);
          break;
      }
    }
  }

  {
    float yOffset = rect.y + rect.width + 40;

    int selection = (int)colorEditMode;
    GuiToggleGroup(Rectangle{rect.x + 10, yOffset, (rect.width - 40) / 2, 20},
                   "Fill;Stroke", (int*)&selection);

    colorEditMode = (ColorMode)(selection);
  }

  {
    float yOffset = rect.y + rect.width + 70;

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
      // TODO: register a command on mouse up
      editedFig->setStrokeWeight(f);
    }
  }
}

void ui::FigurePropertiesPanel::setFigure(
    std::shared_ptr<figure::Figure> newFig) {
  editedFig = std::move(newFig);
}

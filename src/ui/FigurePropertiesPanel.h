#pragma once

#include <memory>

#include "../figure/Figure.h"
#include "Widget.h"

namespace ui {

class FigurePropertiesPanel : public Widget {
  std::shared_ptr<figure::Figure> editedFig = {};

  enum class ColorMode {
    Fill = 0,
    Stroke,
  };

  ColorMode colorEditMode = ColorMode::Fill;

 public:
  ~FigurePropertiesPanel() override = default;

  void update() override;

  void setFigure(std::shared_ptr<figure::Figure> newFig);
};

}  // namespace ui

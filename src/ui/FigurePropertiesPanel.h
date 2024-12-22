#pragma once

#include <memory>

#include "../Document.h"
#include "../commands/ChangeFigurePropsCommand.h"
#include "../figure/Figure.h"
#include "Widget.h"

namespace ui {

class FigurePropertiesPanel : public Widget {
  std::shared_ptr<Document> doc = {};
  std::shared_ptr<figure::Figure> editedFig = {};
  command::ChangeFigurePropsCommand::FigureProps startFigProps;
  bool uncommitedChanges = false;

  enum class ColorMode {
    Fill = 0,
    Stroke,
  };

  ColorMode colorEditMode = ColorMode::Fill;

 public:
  ~FigurePropertiesPanel() override = default;

  void update() override;

  void setDocument(std::shared_ptr<Document> doc);
  void setFigure(std::shared_ptr<figure::Figure> newFig);

 private:
  void registerChangePropsCommand();
};

}  // namespace ui

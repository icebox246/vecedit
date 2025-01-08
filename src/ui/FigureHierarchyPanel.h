#pragma once

#include <memory>
#include <unordered_set>

#include "../Document.h"
#include "../figure/Figure.h"
#include "Widget.h"

namespace ui {

class FigureHierarchyPanel : public Widget {
  std::shared_ptr<Document> doc = {};
  std::unordered_set<std::shared_ptr<figure::Figure>> markedFigures = {};
  std::weak_ptr<class Editor> editor;

 public:
  ~FigureHierarchyPanel() override = default;

  void update() override;

  void setDocument(std::shared_ptr<Document> newDoc);

  void markFigure(std::shared_ptr<figure::Figure> fig);

  void unmarkFigures();

  void setEditor(std::weak_ptr<class Editor>);
};

}  // namespace ui

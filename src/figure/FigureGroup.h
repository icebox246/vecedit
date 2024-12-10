#pragma once

#include "FigureBase.h"

namespace figure {

class FigureGroup : public FigureBase<FigureGroup> {
  std::vector<std::shared_ptr<Figure>> children;

 public:
  ~FigureGroup() override = default;

  void addChild(std::shared_ptr<Figure> figure) {
    children.emplace_back(std::move(figure));
  }
  void removeChild(std::shared_ptr<Figure> figure) {
    children.erase(std::ranges::find(children, figure));
  }
  const std::vector<std::shared_ptr<Figure>>& getChildren() { return children; }

  std::shared_ptr<PointEditor> makePointEditor() override {
    assert(false && "TODO: unimplemented");
  }
};

}  // namespace figure

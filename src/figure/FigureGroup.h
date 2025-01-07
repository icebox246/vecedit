#pragma once

#include <cassert>
#include <memory>

#include "Figure.h"

namespace figure {

class FigureGroup : public Figure,
                    public std::enable_shared_from_this<FigureGroup> {
  std::vector<std::shared_ptr<Figure>> children;

 public:
  ~FigureGroup() override = default;

  std::shared_ptr<Figure> clone() override;

  Vector2 getOrigin() override;

  void setOrigin(Vector2 origin) override;

  void accept(visitor::FigureVisitor& vis) override;

  Color getFill() override;

  void setFill(Color c) override;

  Color getStroke() override;

  void setStroke(Color c) override;

  float getStrokeWeight() override;

  void setStrokeWeight(float w) override;

  void addChild(std::shared_ptr<Figure> figure);

  void removeChild(std::shared_ptr<Figure> figure);

  const std::vector<std::shared_ptr<Figure>>& getChildren();

  std::shared_ptr<PointEditor> makePointEditor() override;
};

}  // namespace figure

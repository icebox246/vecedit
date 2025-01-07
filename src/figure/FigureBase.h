#pragma once

#include <raylib.h>
#include <cassert>
#include <memory>

#include "Figure.h"

namespace figure {

template <typename FigureType>
class FigureBase : public Figure,
                   public std::enable_shared_from_this<FigureType> {
 protected:
  Vector2 origin;
  Color fill, stroke;
  float strokeWeight;

  std::weak_ptr<FigureGroup> transientParent;

 public:
  ~FigureBase() override = default;

  std::shared_ptr<Figure> clone() override {
    return std::make_shared<FigureType>(*dynamic_cast<FigureType*>(this));
  }

  Vector2 getOrigin() override { return origin; }
  void setOrigin(Vector2 newOrigin) override { origin = newOrigin; }

  void accept(visitor::FigureVisitor& vis) override {
    auto ptr = FigureType::shared_from_this();
    vis.visit(ptr);
  }

  Color getFill() override { return fill; }
  void setFill(Color c) override { fill = c; }

  Color getStroke() override { return stroke; }
  void setStroke(Color c) override { stroke = c; }

  float getStrokeWeight() override { return strokeWeight; }
  void setStrokeWeight(float w) override { strokeWeight = w; }

  void updateParent(std::shared_ptr<FigureGroup> parent = nullptr) override {
    transientParent = parent;
  }
  std::shared_ptr<FigureGroup> getParent() override {
    return transientParent.lock();
  }
};

}  // namespace figure

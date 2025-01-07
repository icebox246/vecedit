#pragma once

#include <raylib.h>
#include <memory>

#include "PointEditor.h"
#include "visitor/FigureVisitor.h"

namespace figure {

class Figure {
 public:
  virtual ~Figure() = default;

  virtual std::shared_ptr<Figure> clone() = 0;

  virtual Vector2 getOrigin() = 0;
  virtual void setOrigin(Vector2 origin) = 0;

  virtual void accept(visitor::FigureVisitor& vis) = 0;

  virtual std::shared_ptr<PointEditor> makePointEditor() = 0;

  virtual Color getFill() = 0;
  virtual void setFill(Color c) = 0;

  virtual Color getStroke() = 0;
  virtual void setStroke(Color c) = 0;

  virtual float getStrokeWeight() = 0;
  virtual void setStrokeWeight(float w) = 0;

  virtual void updateParent(std::shared_ptr<class FigureGroup> parent = nullptr) = 0;
  virtual std::shared_ptr<class FigureGroup> getParent() = 0;
};

}  // namespace figure

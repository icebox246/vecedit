#include "FigureGroup.h"

#include <raymath.h>

#include "adapter/FigureGroupPointEditor.h"

using namespace figure;

std::shared_ptr<Figure> FigureGroup::clone() {
  auto res = std::make_shared<FigureGroup>();
  for (auto& c : children) {
    res->addChild(c->clone());
  }
  return res;
}

Vector2 FigureGroup::getOrigin() {
  if (children.empty())
    return {};

  auto res = Vector2{};

  for (auto& c : children) {
    res += c->getOrigin();
  }

  return res / children.size();
}

void FigureGroup::setOrigin(Vector2 origin) {
  auto oldOrigin = getOrigin();

  for (auto& c : children) {
    auto offset = c->getOrigin() - oldOrigin;
    c->setOrigin(origin + offset);
  }
}

void FigureGroup::accept(visitor::FigureVisitor& vis) {
  vis.visit(shared_from_this());
}

Color FigureGroup::getFill() {
  if (children.size()) {
    return children.front()->getFill();
  }
  return {};
}

void FigureGroup::setFill(Color c) {
  if (children.size()) {
    return children.front()->setFill(c);
  }
}

Color FigureGroup::getStroke() {
  if (children.size()) {
    return children.front()->getStroke();
  }
  return {};
}

void FigureGroup::setStroke(Color c) {
  if (children.size()) {
    return children.front()->setStroke(c);
  }
}

float FigureGroup::getStrokeWeight() {
  if (children.size()) {
    return children.front()->getStrokeWeight();
  }
  return {};
}

void FigureGroup::setStrokeWeight(float w) {
  if (children.size()) {
    return children.front()->setStrokeWeight(w);
  }
}

void FigureGroup::addChild(std::shared_ptr<Figure> figure) {
  children.emplace_back(std::move(figure));
}

void FigureGroup::removeChild(std::shared_ptr<Figure> figure) {
  children.erase(std::ranges::find(children, figure));
}

const std::vector<std::shared_ptr<Figure>>& FigureGroup::getChildren() {
  return children;
}

std::shared_ptr<PointEditor> FigureGroup::makePointEditor() {
  using namespace adapter;
  return std::make_shared<FigureGroupPointEditor>(shared_from_this());
}

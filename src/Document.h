#pragma once

#include <raylib.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "figure/Figure.h"

class Document {
  inline static std::map<std::string, std::shared_ptr<Document>> documents;

  Document();
  Document(const Document&) = default;
  Document(Document&&) = default;

  Vector2 dimensions;
  std::vector<std::shared_ptr<figure::Figure>> figures;

 public:
  static std::shared_ptr<Document> getDocument(const std::string_view& name);
  static std::vector<std::string_view> getDocumentNames();

  Vector2 getDimenstions();
  void setDimenstions(Vector2 newDims);
  const std::vector<std::shared_ptr<figure::Figure>>& getFigures();
  void addFigure(std::shared_ptr<figure::Figure> figure);
};

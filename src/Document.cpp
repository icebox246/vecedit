#include "Document.h"

#include <algorithm>

Document::Document() {}

std::shared_ptr<Document> Document::getDocument(const std::string_view& name) {
  if (auto s = std::string(name); documents.contains(s)) {
    return documents.at(s);
  } else {
    auto [it, _] = documents.emplace(
        s, new Document());  // This is not a good way to allocate shared
                             // objects, but to force multiton behaviour it had
                             // to be done this way
    return it->second;
  }
}

std::vector<std::string_view> Document::getDocumentNames() {
  std::vector<std::string_view> result;

  std::ranges::transform(documents, std::back_inserter(result),
                         [](auto& p) { return std::string_view(p.first); });

  return result;
}

Vector2 Document::getDimenstions() {
  return dimensions;
}

void Document::setDimenstions(Vector2 newDims) {
  dimensions = newDims;
}

const std::vector<std::shared_ptr<figure::Figure>>& Document::getFigures() {
  return figures;
}

void Document::addFigure(std::shared_ptr<figure::Figure> figure) {
  figures.emplace_back(std::move(figure));
}

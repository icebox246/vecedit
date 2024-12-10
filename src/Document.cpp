#include "Document.h"

#include <algorithm>

Document::Document() {}

std::shared_ptr<Document> Document::getDocument(
    const std::filesystem::path& path) {
  const auto absPath = std::filesystem::absolute(path);

  if (documents.contains(absPath)) {
    return documents.at(absPath);
  } else {
    auto [it, _] = documents.emplace(
        absPath, new Document());  // This is not a good way to allocate shared
                                   // objects, but to force multiton behaviour
                                   // it had to be done this way
    return it->second;
  }
}

std::vector<std::filesystem::path> Document::getDocumentNames() {
  std::vector<std::filesystem::path> result;

  std::ranges::transform(documents, std::back_inserter(result),
                         [](auto& p) { return p.first; });

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

void Document::removeFigure(std::shared_ptr<figure::Figure> figure) {
  figures.erase(std::ranges::find(figures, figure));
}

const std::filesystem::path& Document::getFilePath() {
  auto it = std::find_if(documents.begin(), documents.end(),
                         [this](auto& p) { return p.second.get() == this; });

  return it->first;
}

command::CommandManager& Document::getCommandManager() {
  return commandManager;
}

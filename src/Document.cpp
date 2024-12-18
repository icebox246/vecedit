#include "Document.h"

#include <algorithm>

Document::Document() : root(std::make_shared<figure::FigureGroup>()) {}

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
  return root->getChildren();
}

void Document::addFigure(std::shared_ptr<figure::Figure> figure) {
  root->addChild(std::move(figure));
}

void Document::removeFigure(std::shared_ptr<figure::Figure> figure) {
  root->removeChild(std::move(figure));
}

const std::filesystem::path& Document::getFilePath() {
  auto it = std::find_if(documents.begin(), documents.end(),
                         [this](auto& p) { return p.second.get() == this; });

  return it->first;
}

command::CommandManager& Document::getCommandManager() {
  return commandManager;
}

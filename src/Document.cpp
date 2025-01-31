#include "Document.h"

#include <algorithm>

Document::Document() : root(std::make_shared<figure::FigureGroup>()) {}

std::shared_ptr<Document> Document::getDocument(
    const std::filesystem::path& path) {
  const auto absPath = std::filesystem::absolute(path);

  if (auto it =
          std::find_if(documents.begin(), documents.end(),
                       [&path](auto& d) { return d->getFilePath() == path; });
      it != documents.end()) {
    return *it;
  } else {
    // This is not a good way to allocate shared
    // objects, but to force multiton behaviour
    // it had to be done this way
    auto doc = std::shared_ptr<Document>(new Document());
    doc->filepath = path;
    documents.push_back(doc);
    return doc;
  }
}

std::vector<std::filesystem::path> Document::getDocumentNames() {
  std::vector<std::filesystem::path> result;

  std::ranges::transform(documents, std::back_inserter(result),
                         [](auto& d) { return d->getFilePath(); });

  return result;
}

Vector2 Document::getDimensions() {
  return dimensions;
}

void Document::setDimenstions(Vector2 newDims) {
  dimensions = newDims;
}

const std::filesystem::path& Document::getFilePath() {
  return filepath;
}

void Document::setFilePath(std::filesystem::path newPath) {
  filepath = std::move(newPath);
}

command::CommandManager& Document::getCommandManager() {
  return commandManager;
}

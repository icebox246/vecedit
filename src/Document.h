#pragma once

#include <raylib.h>
#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include "commands/CommandManager.h"
#include "figure/Figure.h"
#include "figure/FigureGroup.h"

class Document {
  inline static std::map<std::filesystem::path, std::shared_ptr<Document>>
      documents;

  Document();
  Document(const Document&) = default;
  Document(Document&&) = default;

  command::CommandManager commandManager;

  Vector2 dimensions;
  std::shared_ptr<figure::FigureGroup> root;

 public:
  static std::shared_ptr<Document> getDocument(
      const std::filesystem::path& path);
  static std::vector<std::filesystem::path> getDocumentNames();

  Vector2 getDimenstions();
  void setDimenstions(Vector2 newDims);
  std::shared_ptr<figure::FigureGroup> getRoot() { return root; }
  // TODO: remove
  const std::vector<std::shared_ptr<figure::Figure>>& getFigures();
  // TODO: remove
  void addFigure(std::shared_ptr<figure::Figure> figure);
  // TODO: remove
  void removeFigure(std::shared_ptr<figure::Figure> figure);
  const std::filesystem::path& getFilePath();

  command::CommandManager& getCommandManager();
};

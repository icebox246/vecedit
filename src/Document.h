#pragma once

#include <raylib.h>
#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include "commands/CommandManager.h"
#include "figure/Figure.h"

class Document {
  inline static std::map<std::filesystem::path, std::shared_ptr<Document>>
      documents;

  Document();
  Document(const Document&) = default;
  Document(Document&&) = default;

  command::CommandManager commandManager;

  Vector2 dimensions;
  std::vector<std::shared_ptr<figure::Figure>> figures;

 public:
  static std::shared_ptr<Document> getDocument(
      const std::filesystem::path& path);
  static std::vector<std::filesystem::path> getDocumentNames();

  Vector2 getDimenstions();
  void setDimenstions(Vector2 newDims);
  const std::vector<std::shared_ptr<figure::Figure>>& getFigures();
  void addFigure(std::shared_ptr<figure::Figure> figure);
  void removeFigure(std::shared_ptr<figure::Figure> figure);
  const std::filesystem::path& getFilePath();

  command::CommandManager& getCommandManager();
};

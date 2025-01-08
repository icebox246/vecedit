#pragma once

#include <raylib.h>
#include <cassert>
#include <filesystem>
#include <string>

#include "RendererVisitor.h"

namespace figure::visitor {

class BitmapRendererVisitor : public RendererVisitor {
  RenderTexture renderTex;
  std::string imgFormat;

 public:
  BitmapRendererVisitor(std::string imgFormat, Vector2 dimensions)
      : imgFormat(std::move(imgFormat)) {
    renderTex = LoadRenderTexture(dimensions.x, dimensions.y);
  }
  virtual ~BitmapRendererVisitor() { UnloadRenderTexture(renderTex); }

  void beginMode() { BeginTextureMode(renderTex); }
  void endAndSaveToFile(const std::filesystem::path& filepath) {
    EndTextureMode();

    auto fp = filepath;
    if (fp.extension() != "." + imgFormat) {
      fp.replace_filename(
          std::format("{}.{}", fp.filename().string(), imgFormat));
    }

    TraceLog(LOG_INFO, TextFormat("Saved to %s", fp.c_str()));

    Image img = LoadImageFromTexture(renderTex.texture);

    ExportImage(img, fp.c_str());

    UnloadImage(img);
  }
};

}  // namespace figure::visitor

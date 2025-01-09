#pragma once

namespace command {

class Command {
 public:
  virtual ~Command() = default;
  virtual void execute() = 0;
  virtual void unexecute() = 0;
};

}  // namespace command

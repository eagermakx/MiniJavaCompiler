#pragma once

#include "IR/wrappers/SubtreeWrapper.h"
#include "IR/ir_nodes.h"

namespace IR {

class BaseCondWrapper : public SubtreeWrapper {
 public:
  virtual ~BaseCondWrapper() = default;
  BaseExp* ToExp() override;
  BaseStm* ToStm() override;
};

}
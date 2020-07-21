#pragma once

#include "IR/ir_nodes.h"
#include "IR/generators/Label.h"

namespace IR {

class SubtreeWrapper {
 public:
  virtual ~SubtreeWrapper() = default;
  virtual BaseExp *ToExp() = 0;
  virtual BaseStm *ToStm() = 0;
  virtual BaseStm *ToCond(Label true_label, Label false_label) = 0;
};

}

#pragma once

#include "SubtreeWrapper.h"
#include "IR/ir_nodes.h"

namespace IR {

class ExpWrapper : public SubtreeWrapper {
 public:
  explicit ExpWrapper(BaseExp *exp);
  
  BaseExp* ToExp() override;
  BaseStm* ToStm() override;
  BaseStm* ToCond(Label true_label, Label false_label) override;
 
 private:
  BaseExp *exp_;
};

}

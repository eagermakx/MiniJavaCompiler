#pragma once

#include "SubtreeWrapper.h"
#include "IR/ir_nodes.h"

namespace IR {

class StmWrapper : public SubtreeWrapper {
 public:
  StmWrapper(BaseStm* stm);
  
  BaseExp *ToExp() override;
  
  BaseStm *ToStm() override;
  
  BaseStm *ToCond(Label true_label, Label false_label) override;
 
 private:
  BaseStm* stm_;
};

}

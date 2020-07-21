#pragma once

#include <vector>
#include "forward_decl.h"
#include <IR/IRBaseNode.h>

namespace IR {

class ExpList : public IR::BaseNode {
 public:
  ExpList() = default;
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  void Add(BaseExp* exp);
  
  std::vector<BaseExp*> list;
};

}
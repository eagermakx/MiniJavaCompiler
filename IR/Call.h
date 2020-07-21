#pragma once

#include "ExpList.h"

namespace IR {

class Call : public BaseExp {
 public:
  Call(Label function, ExpList* args) : function(std::move(function)), args(args) {}
  
  void Accept(IR::Visitor::Base *visitor) override { visitor->Visit(this); }
  
  Label function;
  ExpList* args;
};

} // namespace IR
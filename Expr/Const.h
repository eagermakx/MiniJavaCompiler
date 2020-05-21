//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once
#include "Expr.h"

namespace Expr {

class Const : public Expr::Base {
 public:
  explicit Const(int val) : value(val) {};
  
  void Accept(Visitor::Base *visitor) override;
  
 public:
  int value{0};
};

}

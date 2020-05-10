//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once
#include "Expr.h"

namespace Expr {

class This : public Expr::Base {
 public:
  This() = default;
  
  void Accept(Visitor::Base *visitor) override;
};

}
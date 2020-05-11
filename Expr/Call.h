//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include "Expr.h"
#include <Expr/Id.h>

namespace Expr {

class Call : public Expr::Base {
 public:
  Call(Expr::Base* expr, std::string method);
  
  void Accept(Visitor::Base *visitor) override;
 
 public:
  std::string method_name;
  ClassMethod* actual;
  Expr::Base* expr;
};

}

//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include "Expr.h"
#include <Expr/Id.h>

namespace Expr {

class Call : public Expr::Base {
 public:
  Call(Expr::Base* expr, std::string method, CallParamList* params);
  
  void Accept(Visitor::Base *visitor) override;
 
 public:
  ClassMethod* actual{nullptr};
  Class* cls{nullptr};
  
  std::string method_name;
  Expr::Base* expr;
  CallParamList* passed_params;
};

}

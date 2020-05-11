//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include "Stmt.h"
#include <Expr/Id.h>

namespace Stmt {

class Call : public Stmt::Base {
 public:
  Call(Expr::Id* id, std::string method);
  
  void Accept(Visitor::Base *visitor) override;
 
 public:
  std::string method;
  Expr::Id* id;
};

}

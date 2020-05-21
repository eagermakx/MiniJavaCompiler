//
// Created by Igor Maximov on 11.05.2020.
//

#pragma once
#include "Stmt.h"
#include <Expr/Expr.h>

namespace Stmt {

class ExprStmt : public Stmt::Base {
 public:
  explicit ExprStmt(Expr::Base* expr) : expr(expr) {}
  
  void Accept(Visitor::Base* visitor) override;
 
 public:
  Expr::Base* expr;
};

}

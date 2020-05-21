//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Expr/Id.h"
#include "Stmt.h"
#include "Type/Type.h"

namespace Stmt {
  class VarDecl : public Stmt::Base {
   public:
    explicit VarDecl(Type* type, Expr::Id* var_id);
    
    void Accept(Visitor::Base *visitor) override;
   
   public:
    // Type* type;
    Expr::Id* var_id;
  };
}
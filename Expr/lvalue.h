//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

#include "Expr.h"
#include "Entity/Id.h"

namespace Expr {
  class lvalue : public Expr::Base {
   public:
    explicit lvalue(Entity::Id *id);
  
    void Accept(Visitor::Base *visitor) override;
  
    int eval() const override;
 
   public:
    Entity::Id *id;
  };
}
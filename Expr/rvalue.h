//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

#include "Expr.h"
#include "Entity/Id.h"
#include "Entity/Const.hpp"

namespace Expr {
  class rvalue : public Expr::Base {
   public:
    enum class Type {
      ident,
      constant
    };
    
    explicit rvalue(Entity::Id* id);
    explicit rvalue(Entity::Const* literal);
  
    int eval() const override;
  
    void Accept(Visitor::Base *visitor) override;
 
   public:
    Type type;
    Entity::Id *id;
    Entity::Const *literal;
  };
}

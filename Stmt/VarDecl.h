//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Entity/Id.h"
#include "Stmt.h"

namespace Stmt {
  class VarDecl : public Stmt::Base {
   public:
    explicit VarDecl(Entity::Id *ident) : ident(ident) {}
    
    void Accept(Visitor::Base *visitor) override;
   
   public:
    Entity::Id *ident;
  };
}
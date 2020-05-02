//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include <Type/Type.h>
#include "Entity.h"

namespace Entity {
 class Const : public Entity::Base {
   private:
    using internal_type = int;
   
   public:
    explicit Const(internal_type value) : value(value) {}
    
    ~Const() override = default;
    
    void Accept(Visitor::Base *visitor) override {
      visitor->Visit(this);
    }
   
   public:
    internal_type value;
  };
}
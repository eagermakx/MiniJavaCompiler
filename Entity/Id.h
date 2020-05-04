//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Entity.h"
#include <string>
#include "SymbolTable/Symbol.h"

namespace Entity {
  class Id : public Base {
   public:
    explicit Id(std::string identifier);
    
    void Accept(Visitor::Base *visitor) override;
   
   public:
    std::string identifier;
    Symbol* symbol{nullptr};
  };
}
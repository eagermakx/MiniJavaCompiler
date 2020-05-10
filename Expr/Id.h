//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

#include "Expr.h"
#include "SymbolTable/Symbol.h"

#include <string>

namespace Expr {
class Id : public Expr::Base {
   public:
    explicit Id(std::string identifier);
    
    void Accept(Visitor::Base *visitor) override;
   
   public:
    std::string identifier;
    Symbol symbol;
  };
}
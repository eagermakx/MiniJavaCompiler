//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

#include <vector>
#include "Stmt.h"

namespace Stmt {
  class List : public Stmt::Base {
   public:
    List() = default;
    
    void AddStmt(Stmt::Base *stmt);
    
    void Accept(Visitor::Base *visitor) override;
   
   public:
    std::vector<Stmt::Base *> list;
  };
}

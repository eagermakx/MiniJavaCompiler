//
// Created by Igor Maximov on 03.04.2020.
//

#include "Id.h"

namespace Entity {
  Id::Id(std::string identifier) : identifier(std::move(identifier)) {}
  
  void Id::Accept(Visitor::Base *visitor) {
    visitor->Visit(this);
  }
}


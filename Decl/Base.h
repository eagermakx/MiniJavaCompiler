//
// Created by Igor Maximov on 08.05.2020.
//

#pragma once
#include "BaseNode.h"
#include "SymbolTable/Symbol.h"
#include <cassert>

namespace Decl {

class Base : public BaseNode {
 public:
  Symbol symbol;
};

}
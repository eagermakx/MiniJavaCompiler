//
// Created by Igor Maximov on 03.05.2020.
//

#include "UninitObject.h"
#include <exception>
#include <stdexcept>

int UninitObject::ToInt() {
  throw std::runtime_error("Variable not initialized");
}

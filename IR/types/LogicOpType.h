#pragma once

#include <string>

namespace IR {

enum class LogicOpType : char {
  GT,
  LT,
  GE,
  LE,
  E,
  NE
};

std::string ToString(LogicOpType type);
std::string AsmRepr(LogicOpType type);

}

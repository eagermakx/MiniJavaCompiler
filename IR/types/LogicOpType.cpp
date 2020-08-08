#include "LogicOpType.h"

namespace IR {

std::string ToString(LogicOpType type) {
  switch (type) {
    case LogicOpType::E: return "==";
    case LogicOpType::NE: return "!=";
    case LogicOpType::GE: return ">=";
    case LogicOpType::LE: return "<=";
    case LogicOpType::GT: return ">";
    case LogicOpType::LT: return "<";
  }
}

std::string AsmRepr(LogicOpType type) {
  switch (type) {
    case LogicOpType::E: return "z";
    case LogicOpType::NE: return "nz";
    case LogicOpType::GE: return "ge";
    case LogicOpType::LE: return "le";
    case LogicOpType::GT: return "gt";
    case LogicOpType::LT: return "lt";
  }
}

}

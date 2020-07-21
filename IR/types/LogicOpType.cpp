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

}

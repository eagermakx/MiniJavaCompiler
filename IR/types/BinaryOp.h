#pragma once

#include <string>
#include <Expr/BinaryOp.h>

namespace IR {

enum class BinaryOpType : char {
  PLUS,
  MINUS,
  MUL,
  DIV,
  AND,
  OR
};

std::string ToString(BinaryOpType type);

BinaryOpType AST_to_IR_transform(Expr::BinOperationType ast_binop_type);

} // namespace IR

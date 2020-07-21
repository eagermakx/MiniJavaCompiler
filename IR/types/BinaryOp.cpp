#include "BinaryOp.h"

namespace IR {

std::string ToString(BinaryOpType type) {
  switch (type) {
    case BinaryOpType::AND: return "and";
    case BinaryOpType::DIV: return "/";
    case BinaryOpType::MINUS: return "-";
    case BinaryOpType::PLUS: return "+";
    case BinaryOpType::MUL: return "*";
    case BinaryOpType::OR: return "or";
  }
}

BinaryOpType AST_to_IR_transform(Expr::BinOperationType ast_binop_type) {
  switch (ast_binop_type) {
    case Expr::BinOperationType::Add: return BinaryOpType::PLUS;
    case Expr::BinOperationType::Sub: return BinaryOpType::MINUS;
    case Expr::BinOperationType::Div: return BinaryOpType::DIV;
    case Expr::BinOperationType::Mul: return BinaryOpType::MUL;
    default: std::cerr << "Too bad :)\nUnsupported binary operation\n"; exit(1);
  }
}

}

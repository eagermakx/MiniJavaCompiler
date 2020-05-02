//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

class Program;

namespace Entity {
  class Base;
  class Const;
  class Id;
}

namespace Expr {
  class Base;
  class BinaryOp;
  class UnaryOp;
  class lvalue;
  class rvalue;
}

namespace Stmt {
  class Base;
  class Assign;
  class Cond;
  class Print;
  class Ret;
  class VarDecl;
  class List;
}

//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

class Program;

namespace Expr {
  class Base;
  class BinaryOp;
  class UnaryOp;
  class Const;
  class Id;
  class This;
}

namespace Stmt {
  class Base;
  class Assign;
  class Cond;
  class Print;
  class Ret;
  class VarDecl;
  class List;
  class ScopedList;
  class Call;
  class New;
}

namespace Decl {
  class Base;
}

class ProgramBody;
class Class;
class ClassBody;
class ClassField;
class ClassMethod;
class MainClass;
class FuncParamList;
class FuncParameter;

class Type;
class Int;
class Bool;
class UserType;
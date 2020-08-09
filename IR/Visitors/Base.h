//
// Created by Igor Maximov on 21.07.2020.
//

#pragma once

#include <IR/forward_decl.h>

namespace IR {

namespace Visitor {
class Base {
 public:
  virtual void Visit(Binop* binop) = 0;
  virtual void Visit(Call* call) = 0;
  virtual void Visit(CJump* cjump) = 0;
  virtual void Visit(Const* cnst) = 0;
  virtual void Visit(Eseq* eseq) = 0;
  virtual void Visit(Exp* exp) = 0;
  virtual void Visit(ExpList* exp_list) = 0;
  virtual void Visit(Jump* jump) = 0;
  virtual void Visit(Mem* mem) = 0;
  virtual void Visit(Move* move) = 0;
  virtual void Visit(Name* name) = 0;
  virtual void Visit(Seq* seq) = 0;
  virtual void Visit(SetLabel* set_label) = 0;
  virtual void Visit(TempExp* temp_expr) = 0;
  virtual void Visit(Register* reg) = 0;
};
}

}

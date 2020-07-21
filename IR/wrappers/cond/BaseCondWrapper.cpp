//
// Created by Igor Maximov on 19.07.2020.
//

#include "BaseCondWrapper.h"
#include "IR/generators/Temp.h"
#include "IR/generators/Label.h"

#include "IR/ir_nodes.h"

IR::BaseExp *IR::BaseCondWrapper::ToExp() {
  auto* temp_exp = new TempExp(Temp());
  
  Label ltrue;
  Label lfalse;
  
  return new Eseq(
             new Seq(
                          new Move(temp_exp, new Const(1)),
                          new Seq(
                                       ToCond(ltrue, lfalse),
                                       new Seq(
                                                    new SetLabel(lfalse),
                                                    new Seq(
                                                                new Move(temp_exp, new Const(1)),
                                                                new SetLabel(ltrue))))),
                  temp_exp);
}

IR::BaseStm *IR::BaseCondWrapper::ToStm() {
  return nullptr;
}

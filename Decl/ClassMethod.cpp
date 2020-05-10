//
// Created by Igor Maximov on 08.05.2020.
//

#include <Functions/FuncParamList.h>
#include "ClassMethod.h"

ClassMethod::ClassMethod(Type *out, std::string name, FuncParamList *params, Stmt::List *list, bool is_static)
    : out(out),
      parameters(std::move(params->parameters)),
      name(std::move(name)),
      statements(list),
      is_static(is_static) {
}

void ClassMethod::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

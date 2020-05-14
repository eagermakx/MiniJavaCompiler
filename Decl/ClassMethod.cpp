//
// Created by Igor Maximov on 08.05.2020.
//

#include <Functions/FuncParamList.h>
#include <Type/Type.h>

#include "ClassMethod.h"

ClassMethod::ClassMethod(Type *out, std::string name, FuncParamList *params, Stmt::List *list, bool is_static)
    : out(out),
      params(std::move(params->params)),
      name(std::move(name)),
      statements(list),
      is_static(is_static) {
}

void ClassMethod::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

std::string ClassMethod::Representation() {
  std::string ans = Repr(out) + " " + name + "(";
  
  for (int i = 0; i < params.size(); ++i) {
    ans += Repr(params[i].type) + " " + params[i].name;
    if (i != params.size() - 1) {
      ans += ", ";
    }
  }
  
  ans += ")";
  return ans;
}

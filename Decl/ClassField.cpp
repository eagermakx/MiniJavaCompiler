//
// Created by Igor Maximov on 08.05.2020.
//

#include "ClassField.h"

#include <Type/Type.h>

ClassField::ClassField(Type *type, std::string label) : type(type), name(std::move(label)) {
}

void ClassField::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

size_t ClassField::EvaluateFieldSize() {
  assert(IsPrimitive(type));
  
}

//
// Created by Igor Maximov on 11.05.2020.
//

#include "New.h"

Expr::New::New(std::string class_name) : class_name(std::move(class_name)) {
}

void Expr::New::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

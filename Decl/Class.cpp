//
// Created by Igor Maximov on 08.05.2020.
//

#include "Class.h"
#include "ClassBody.h"

Class::Class(std::string label, ClassBody *body) : name(std::move(label)) {
  methods = std::move(body->methods);
  fields = std::move(body->fields);
}

void Class::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

Class::Class(std::string name) : name(std::move(name)) {
}

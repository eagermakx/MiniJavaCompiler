//
// Created by Igor Maximov on 08.05.2020.
//

#include "Class.h"
#include "ClassBody.h"

Class::Class(std::string label, ClassBody *body)
    : name(std::move(label)),
      methods(std::move(body->methods)),
      fields(std::move(body->fields)) {
  
  size_t current_offset = 0;
  for (auto* field : fields) {
    fields_offsets.emplace(field, current_offset);
    current_offset += 1;
  }
  
  for (auto* method : methods) {
    method->owner = this;
  }
}

void Class::Accept(Visitor::Base *visitor) {
  visitor->Visit(this);
}

Class::Class(std::string name) : name(std::move(name)) {
}

size_t Class::EvaluateObjectSize() {
  size_t ans = 0;
  for (auto* field : fields) {
    ans += field->EvaluateFieldSize();
  }
}

bool Class::FieldExists(ClassField* field) const {
  return fields_offsets.find(field) != fields_offsets.end();
}

size_t Class::GetFieldOffset(ClassField* field) const {
  assert(FieldExists(field));
  return fields_offsets.at(field);
}

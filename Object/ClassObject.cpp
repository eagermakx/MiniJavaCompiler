//
// Created by Igor Maximov on 11.05.2020.
//

#include "ClassObject.h"
#include "Integer.h"
#include "Boolean.h"
#include <iostream>

std::shared_ptr<Object> ClassObject::AccessField(ClassField *field) {
  return fields[instance_of->GetFieldOffset(field)];
}

ClassObject::ClassObject(Class *cls) : instance_of(cls) {
  for (auto* field : cls->fields) {
    assert(IsPrimitive(field->type));
    fields.push_back(CreateObjectFromType(field->type));
  }
}

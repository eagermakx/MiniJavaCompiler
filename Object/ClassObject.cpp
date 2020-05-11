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
    fields.push_back(ObjectFromType(field->type));
  }
}

std::shared_ptr<Object> ClassObject::ObjectFromType(Type *type) {
  switch (type->type) {
    case Type::PossibleTypes::Int: return std::make_shared<Integer>(0);
    case Type::PossibleTypes::Bool: return std::make_shared<Boolean>(0);
    case Type::PossibleTypes::UserType: std::cerr << "User types as class fields are not supported yet" << std::endl; exit(1);
    case Type::PossibleTypes::Void: std::cerr << "Can not declare a field of type 'void'" << std::endl; exit(1);
  }
}

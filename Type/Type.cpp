//
// Created by Igor Maximov on 11.05.2020.
//

#include "Type.h"
#include "UserType.h"

std::string Repr(Type* type) {
  assert(type);
  
  switch (type->type) {
    case Type::PossibleTypes::Int: return "int";
    case Type::PossibleTypes::Void: return "void";
    case Type::PossibleTypes::Bool: return "bool";
    case Type::PossibleTypes::UserType: return ((UserType*)type)->class_name;
  }
}

bool SameType(Type* lhs, Type* rhs) {
  assert(lhs && rhs);
  bool ans;
  if (lhs->type == rhs->type) {
    if (lhs->type == Type::PossibleTypes::UserType) {
      return ((UserType*)lhs)->class_name == ((UserType*)rhs)->class_name;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool IsInt(Type* type) {
  assert(type);
  return type->type == Type::PossibleTypes::Int;
}

bool IsBool(Type* type) {
  assert(type);
  return type->type == Type::PossibleTypes::Bool;
}

bool IsVoid(Type* type) {
  assert(type);
  return type->type == Type::PossibleTypes::Void;
}

bool IsPrimitive(Type* type) {
  assert(type);
  return type->type != Type::PossibleTypes::UserType;
}

size_t SizeOf(Type* type) {
  return 0;
}

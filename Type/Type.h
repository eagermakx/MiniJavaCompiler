//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once

class Void;
class Int;
class Bool;

#include <string>

struct Type {
  enum class PossibleTypes {
    Int,
    Bool,
    Void,
    UserType
  };
  
  explicit Type(PossibleTypes type) : type(type) {}
  
  PossibleTypes type;
};

std::string Repr(Type* type);

bool SameType(Type* lhs, Type* rhs);

bool IsInt(Type* type);

bool IsBool(Type* type);

bool IsVoid(Type* type);

bool IsPrimitive(Type* type);

size_t SizeOf(Type* type);
//
// Created by Igor Maximov on 11.05.2020.
//

#include "Object.h"
#include "Integer.h"
#include "Boolean.h"

#include <iostream>

std::shared_ptr<Object> CreateObjectFromType(Type *type) {
  switch (type->type) {
    case Type::PossibleTypes::Int: return std::make_shared<Integer>(0);
    case Type::PossibleTypes::Bool: return std::make_shared<Boolean>(0);
    case Type::PossibleTypes::UserType: std::cerr << "User types as class fields are not supported yet" << std::endl; exit(1);
    case Type::PossibleTypes::Void: std::cerr << "Can not declare a field of type 'void'" << std::endl; exit(1);
  }
}
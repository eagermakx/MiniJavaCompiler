//
// Created by Igor Maximov on 11.05.2020.
//

#include "Object.h"
#include "Integer.h"
#include "Boolean.h"

#include <iostream>

std::shared_ptr<Object> CreateObjectFromType(Type *type) {
  UserType* user_type;
  
  switch (type->type) {
    case Type::PossibleTypes::Int: return std::make_shared<Integer>(0);
    
    case Type::PossibleTypes::Bool: return std::make_shared<Boolean>(0);
    
    case Type::PossibleTypes::UserType:
      user_type = (UserType*)type;
      return std::make_shared<ClassObject>(user_type->instance_of);
      
    case Type::PossibleTypes::Void: std::cerr << "Can not declare a field of type 'void'" << std::endl; exit(1);
  }
}
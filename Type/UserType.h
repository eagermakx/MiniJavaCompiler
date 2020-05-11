//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once

#include "Type.h"
#include <string>

struct UserType : public Type {
  explicit UserType(std::string name) : Type(PossibleTypes::UserType), class_name(std::move(name)) {}
  
  std::string class_name;
};

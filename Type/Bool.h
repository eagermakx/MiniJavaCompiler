//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once
#include "Type.h"

struct Bool : public Type {
  Bool() : Type(PossibleTypes::Bool) {}
};

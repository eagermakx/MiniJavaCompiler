//
// Created by Igor Maximov on 09.05.2020.
//

#pragma once
#include "Type.h"

struct Int : public Type {
  Int() : Type(PossibleTypes::Int) {}
};

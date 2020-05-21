//
// Created by Igor Maximov on 10.05.2020.
//

#pragma once
#include "Type.h"

struct Void : public Type {
  Void() : Type(PossibleTypes::Void) {}
};
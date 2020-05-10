//
// Created by Igor Maximov on 10.05.2020.
//

#pragma once

#include <vector>
#include <string>
#include <Type/Type.h>

#include "FuncParameter.h"

class FuncParamList {
 public:
  FuncParamList() = default;
  
  void AddParameter(FuncParameter* parameter);
  
  std::vector<FuncParameter> parameters;
};

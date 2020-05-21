//
// Created by Igor Maximov on 15.05.2020.
//

#pragma once

#include <Expr/Expr.h>
#include <vector>

class CallParamList {
 public:
  CallParamList() = default;
  
  void AddParameter(Expr::Base* expr);
  
  std::vector<Expr::Base*> params;
};
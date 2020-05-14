//
// Created by Igor Maximov on 15.05.2020.
//

#include "CallParamList.h"

void CallParamList::AddParameter(Expr::Base *expr) {
  params.push_back(expr);
}

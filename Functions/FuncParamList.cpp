//
// Created by Igor Maximov on 10.05.2020.
//

#include "FuncParamList.h"

void FuncParamList::AddParameter(FuncParameter* parameter) {
  params.push_back(*parameter);
}

//
// Created by Igor Maximov on 19.07.2020.
//

#include "ExpList.h"

namespace IR {

void ExpList::Add(BaseExp *exp) {
  list.push_back(exp);
}

}
//
// Created by Igor Maximov on 15.05.2020.
//

#pragma once

#include <BaseNode.h>

void CopyLocation(BaseNode* node, yy::location loc) {
  node->loc = loc;
}
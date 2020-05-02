//
// Created by Igor Maximov on 03.04.2020.
//

#pragma once

template <typename T>
class Type {
 public:
  typedef T internal;
};

using Integer = Type<int>;
using Boolean = Type<bool>;

//
// Created by Igor Maximov on 19.07.2020.
//

#include "Temp.h"

static int temp_counter = 0;

namespace IR {

Temp::Temp() : name_("%" + std::to_string(temp_counter++)) {
}

Temp::Temp(std::string name) : name_(std::move(name)) {
}

std::string Temp::ToString() const {
  return name_;
}

}

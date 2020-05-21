//
// Created by Igor Maximov on 10.05.2020.
//

#include "FuncParameter.h"

FuncParameter::FuncParameter(Type *type, std::string name) : type(type), name(std::move(name)) {
}

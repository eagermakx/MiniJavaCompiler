//
// Created by Igor Maximov on 03.05.2020.
//

#include "ScopeLayer.h"



ScopeLayer::ScopeLayer(ScopeLayer *parent) : parent_(parent) {
}

bool ScopeLayer::Exists(Symbol symbol) const {
  return false;
}

void ScopeLayer::Set(Symbol symbol, std::shared_ptr<Object> object) {

}

std::shared_ptr<Object> ScopeLayer::Get(Symbol symbol) const {
  return std::shared_ptr<Object>();
}

void ScopeLayer::Declare(Symbol symbol) {

}

void ScopeLayer::AddChild(ScopeLayer *child) {

}

ScopeLayer *ScopeLayer::GetChild(size_t index) const {
  return nullptr;
}

ScopeLayer *ScopeLayer::GetParent() const {
  return nullptr;
}

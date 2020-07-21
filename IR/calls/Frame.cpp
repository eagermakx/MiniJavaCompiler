//
// Created by Igor Maximov on 19.07.2020.
//

#include "Frame.h"
#include "error.h"
#include "FrameMemPtr.h"
#include "AbsMemPtr.h"

IR::Frame::Frame(Symbol method) : method(std::move(method)) {
  StartScope();
  frame_pointer = new AbsMemPtr();
  return_value_address = new FrameMemPtr(frame_pointer, 2);
  return_address = new FrameMemPtr(frame_pointer, 1);
}

IR::MemPtr *IR::Frame::GetRetValueAddress() const {
  return return_value_address;
}

IR::MemPtr *IR::Frame::GetFramePointer() const {
  return frame_pointer;
}

IR::MemPtr *IR::Frame::GetAddress(Symbol symbol) const {
  return addresses_.at(symbol);
}

int IR::Frame::GetOffset() const {
  return current_offset;
}

void IR::Frame::AddVariable(Symbol symbol) {
  if (addresses_.find(symbol) != addresses_.end()) {
    std::cerr << "Duplicate write to the same symbol in IRFrame" << std::endl;
    exit(1);
  }
  
  AddSymbolToCurrentScope(symbol);
  
  addresses_.emplace(symbol, new FrameMemPtr(frame_pointer, current_offset++));
}

void IR::Frame::StartScope() {
  scopes_.emplace(Scope());
}

void IR::Frame::ExitScope() {
  scopes_.pop();
}

void IR::Frame::AddSymbolToCurrentScope(Symbol symbol) {
  scopes_.top().vars.emplace(std::move(symbol));
}

IR::Frame::Scope IR::Frame::GetCurrentScope() {
  return scopes_.top();
}

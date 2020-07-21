#include "Label.h"

static int label_counter = 0;

IR::Label::Label() : labelname_("L" + std::to_string(label_counter++)) {
}

IR::Label::Label(std::string labelname) : labelname_(std::move(labelname)) {
}

std::string IR::Label::ToString() const {
  return labelname_;
}



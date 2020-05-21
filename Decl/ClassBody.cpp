//
// Created by Igor Maximov on 08.05.2020.
//

#include "ClassBody.h"

void ClassBody::AddMethod(ClassMethod* method) {
  methods.push_back(method);
}

void ClassBody::AddField(ClassField* field) {
  fields.push_back(field);
}


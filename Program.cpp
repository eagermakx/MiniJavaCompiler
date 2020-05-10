//
// Created by Igor Maximov on 10.05.2020.
//

#include <Decl/ProgramBody.h>
#include <Decl/Class.h>
#include <Decl/MainClass.h>
#include "Program.h"

Program::Program(MainClass* main, ProgramBody *class_decls) : classes(std::move(class_decls->classes)), main_class(main) {
}
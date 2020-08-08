//
// Created by Igor Maximov on 07.08.2020.
//

#pragma once
#include "IR/assembly/Instr.h"
#include <vector>
#include "IR/ir_nodes.h"

namespace ASM {

std::vector<ASM::Instr*> SelectInstructions(IR::BaseStm* stm);
// std::vector<ASM::Instr*> SelectInstructions(IR::BaseExp* exp);

} // ASM

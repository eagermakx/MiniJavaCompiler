//
// Created by Igor Maximov on 02.08.2020.
//

#pragma once
#include "ir_nodes.h"
#include "BasicBlock.h"
#include <unordered_map>
#include <IR/Visitors/Linearizer.h>

namespace IR {

using BlockMapping = std::unordered_map<std::string, IR::BasicBlock>;

BlockMapping BasicBlocksSplit(const std::unordered_map<std::string, std::vector<IR::BaseStm *>> &linearizer_output);

std::vector<IR::BasicBlock> TraceReschedule(BlockMapping map, const std::vector<std::string>& method_labels);

std::vector<std::string> GetMethodLabels(const IR::Visitor::Linearizer::List& lin_out);

}

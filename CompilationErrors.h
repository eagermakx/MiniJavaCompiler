//
// Created by Igor Maximov on 15.05.2020.
//

#pragma once

#define ERROR(msg, node) \
std::cerr << *(node->loc.begin.filename) << ":" << node->loc.begin.line << ":" << node->loc.begin.column << " " << msg << std::endl; \
exit(1);

#define COMPILATION_ERROR(msg, node) ERROR(msg, node)

#define RUNTIME_ERROR(msg, node) ERROR(msg, node)

#define ASSERT(e, msg, node) \
if (!e) { COMPILATION_ERROR(msg, node); }

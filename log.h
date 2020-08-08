//
// Created by Igor Maximov on 02.05.2020.
//

#pragma once

#include <iostream>

#define UNREACHABLE(x) do { std::cerr << "[!] Unreachable code area : " << x << std::endl; exit(1); } while (false)

#define NO_LOG

#ifndef NO_LOG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif
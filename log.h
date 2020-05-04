//
// Created by Igor Maximov on 02.05.2020.
//

#pragma once

#include <iostream>

#define UNREACHABLE(x) std::cerr << "[!] Unreachable code area : " << x << std::endl; exit(1);

#define LOG(x) std::cout << x << std::endl
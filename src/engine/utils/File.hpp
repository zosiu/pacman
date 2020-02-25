#pragma once

#ifndef E8C62694_8134_3B0A_124D_F5F70ADB81F9
#define E8C62694_8134_3B0A_124D_F5F70ADB81F9

#include "../../pch.hpp"

namespace engine {

class File {
public:
  static std::string contents(const char *filename);
};

} // namespace engine

#endif /* E8C62694_8134_3B0A_124D_F5F70ADB81F9 */

#include "../../pch.hpp"

#include "File.hpp"

namespace engine {

std::string File::contents(const char *filename) {
  std::ifstream ifs(filename, std::ios::in);
  std::string file_contents((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
  ifs.close();
  return file_contents;
}

} // namespace engine

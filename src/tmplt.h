#ifndef TMPLT_TMPLT_H
#define TMPLT_TMPLT_H
#include "inja.hpp"
#include <string>
#include <sstream>
#include <set>

namespace tmplt {
constexpr int VERSION_MAJOR = 0;
constexpr int VERSION_MINOR = 1;
constexpr int VERSION_PATCH = 0;

inline void die(const std::string &msg) {
  std::cerr << "\x1b[31m" << msg << "\x1b[0m" << std::endl;
  exit(1);
}

inline std::string version() {
  std::ostringstream oss;
  oss << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;
  return oss.str();
}

} // namespace tmplt

#endif

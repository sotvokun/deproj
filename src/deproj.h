#ifndef DEPROJ_DEPROJ_H
#define DEPROJ_DEPROJ_H
#define DEPROJ_VERSION_MAJOR 0
#define DEPROJ_VERSION_MINOR 1
#define DEPROJ_VERSION_PATCH 0

#include <format>
#include <string>
#include <cstdlib>
#include <iostream>
#include <unordered_map>


namespace deproj {

using string_type = std::string;
using variable_dict_type = std::unordered_map<string_type, string_type>;

inline constexpr auto version()
{
    return std::format(
        "{}.{}.{}",
        DEPROJ_VERSION_MAJOR,
        DEPROJ_VERSION_MINOR,
        DEPROJ_VERSION_PATCH
    );
}

inline void die(const std::string &msg, int code = 1)
{
    std::cerr << "\x1b[31m" << msg << "\x1b[0m" << std::endl;
    std::exit(1);
}

string_type render(
    const string_type &template_content,
    const variable_dict_type &variables
);

} // namespace deproj

#endif

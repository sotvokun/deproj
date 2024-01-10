#ifndef DEPROJ_FILE_UTILITY_H
#define DEPROJ_FILE_UTILITY_H

#include <fstream>
#include <filesystem>
#include <format>

#include "deproj.h"

namespace deproj::file_utility {

inline bool exists(const string_type &path)
{
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

inline string_type read(const string_type &path)
{
    std::ifstream ifs(path);
    if (!ifs) {
        die(std::format("cannot open file: {}", path));
    }

    return string_type(
        std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()
    );
}

inline void write(const string_type &path, const string_type &content)
{
    auto parent_path = std::filesystem::path(path).parent_path();

    if (!parent_path.empty() && !std::filesystem::exists(parent_path)) {
        std::filesystem::create_directories(parent_path);
    }

    std::ofstream ofs(path);
    if (!ofs) {
        die(std::format("cannot open file: {}", path));
    }

    ofs << content;
}

} // namespace deproj

#endif

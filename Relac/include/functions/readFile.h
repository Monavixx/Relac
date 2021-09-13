#pragma once

#include <filesystem>
#include <fstream>

#include "logger/logger.h"

namespace fs = std::filesystem;

inline std::string readFile(const fs::path& path) noexcept
{
    Logger::note().log("Read file " + path.string());
    std::ifstream f(path, std::ios::in | std::ios::binary);
    const auto sz = fs::file_size(path);
    std::string txt(sz, 0);
    f.read(txt.data(), sz);
    
    return txt;
}

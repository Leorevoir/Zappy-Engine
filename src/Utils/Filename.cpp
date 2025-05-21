#include "Filename.hpp"
#include <filesystem>

std::string zap::Filename::getPath(const std::string &filename)
{
    if (filename.empty()) {
        return {};
    }
    try {
        return std::filesystem::absolute(filename).string();
    } catch (const std::filesystem::filesystem_error &) {
        return {};
    }
}

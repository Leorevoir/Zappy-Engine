#pragma once

#define ZAP_TYPES_ONLY
#include "GLEngineTypes.hpp"

#include <string>

namespace zap {

struct Texture {
        zap::u32 _id;
        std::string _type;
        std::string _path;
};

}// namespace zap

#pragma once

#include "GLEngineTypes.hpp"
#include <string>

namespace zap {

class Texture final
{
    public:
        explicit Texture(const std::string &path);
        ~Texture();

        void bind(u32 unit = 0) const noexcept;

    private:
        u32 _id;
};

}// namespace zap

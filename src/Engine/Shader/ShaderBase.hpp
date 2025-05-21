#pragma once

#include "GLEngineTypes.hpp"
#include "Macro.hpp"

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <glm/glm.hpp>
#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

namespace zap::abstract {

class ShaderBase
{
    public:
        virtual ~ShaderBase() = default;

        void setBool(const char *RESTRICT name, const bool value) const noexcept;
        void setInt(const char *RESTRICT name, const i32 value) const noexcept;
        void setFloat(const char *RESTRICT name, const f32 value) const noexcept;
        void setVec2(const char *RESTRICT name, const glm::vec2 &value) const noexcept;
        void setVec3(const char *RESTRICT name, const glm::vec3 &value) const noexcept;
        void setVec4(const char *RESTRICT name, const glm::vec4 &value) const noexcept;
        void setMat2(const char *RESTRICT name, const glm::mat2 &value) const noexcept;
        void setMat3(const char *RESTRICT name, const glm::mat3 &value) const noexcept;
        void setMat4(const char *RESTRICT name, const glm::mat4 &value) const noexcept;

        u32 getProgram() const noexcept;

    protected:
        u32 _program = 0;
};
}// namespace zap::abstract

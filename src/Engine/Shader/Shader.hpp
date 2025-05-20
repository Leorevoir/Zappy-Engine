#pragma once

#include "NonCopyable.hpp"
#include "ShaderBase.hpp"

namespace zap {

class Shader final : public abstract::ShaderBase, public abstract::NonCopyable
{

    public:
        explicit Shader(const char *RESTRICT vertex_path, const char *RESTRICT fragment_path, const char *RESTRICT geometry_path = nullptr);
        ~Shader() noexcept override;

        void use() const noexcept;
};
}// namespace zap

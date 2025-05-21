#pragma once

#include "NonCopyable.hpp"
#include "ShaderBase.hpp"
#include <string>

namespace zap {

class Shader final : public abstract::ShaderBase, public abstract::NonCopyable
{

    public:
        explicit Shader(const std::string &vertex_path, const std::string &fragment_path, const std::string &geometry_path = {});
        ~Shader() noexcept override;

        void use() const noexcept;
};
}// namespace zap

#include "Shader.hpp"
#include "Error.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/**
* public
*/

static void _check_compile_errors(GLuint shader, const std::string &type)
{
    GLint success;
    GLchar infoLog[ZAP_INFO_LOG_BUFFER_SIZE];

    if (type != "PROGRAM") {

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, ZAP_INFO_LOG_BUFFER_SIZE, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl
                      << infoLog << std::endl
                      << " -- --------------------------------------------------- -- " << std::endl;
        }

    } else {

        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, ZAP_INFO_LOG_BUFFER_SIZE, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl
                      << infoLog << std::endl
                      << " -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

[[nodiscard]] static const std::string _load_shader_source(const char *shader_path)
{
    std::ifstream shader_file;

    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shader_file.open(shader_path);
        std::stringstream shader_stream;

        shader_stream << shader_file.rdbuf();
        shader_file.close();

        return shader_stream.str();
    } catch (std::ifstream::failure &e) {
        throw zap::exception::Error("Shader::_load_shader_source", "File not successfully read: ", e.what());
    }
}

[[nodiscard]] static GLuint _compile_shader(const char *shader_code, GLenum shader_type, const std::string &type)
{
    GLuint shader = glCreateShader(shader_type);

    glShaderSource(shader, ZAP_DEFAULT_GLSIZEI, &shader_code, NULL);
    glCompileShader(shader);
    _check_compile_errors(shader, type);
    return shader;
}

zap::Shader::Shader(const std::string &vertex_path, const std::string &fragment_path, const std::string &geometry_path)
{
    const std::string vertex_source = _load_shader_source(vertex_path.c_str());
    const std::string fragment_source = _load_shader_source(fragment_path.c_str());
    std::string geometry_source;

    /**
     * @brief get the C-string
     */
    const char *vertex_code = vertex_source.c_str();
    const char *fragment_code = fragment_source.c_str();
    const char *geometry_code = nullptr;

    if (!geometry_path.empty()) {
        geometry_source = _load_shader_source(geometry_path.c_str());
        geometry_code = geometry_source.c_str();
    }

    u32 vertex = _compile_shader(vertex_code, GL_VERTEX_SHADER, "VERTEX");
    u32 fragment = _compile_shader(fragment_code, GL_FRAGMENT_SHADER, "FRAGMENT");
    u32 geometry = ZAP_DEFAULT_VALUE;

    if (!geometry_path.empty()) {
        geometry = _compile_shader(geometry_code, GL_GEOMETRY_SHADER, "GEOMETRY");
    }

    /**
     * @brief bind shaders to our programs
     */
    _program = glCreateProgram();
    glAttachShader(_program, vertex);
    glAttachShader(_program, fragment);

    if (!geometry_path.empty()) {
        glAttachShader(_program, geometry);
    }

    glLinkProgram(_program);

    _check_compile_errors(_program, "PROGRAM");

    /**
     * @brief delete shaders as theyre linked into our program
     */
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (!geometry_path.empty()) {
        glDeleteShader(geometry);
    }
}

zap::Shader::~Shader() noexcept
{
    if (_program != ZAP_DEFAULT_VALUE) {
        glDeleteProgram(_program);
        _program = ZAP_DEFAULT_VALUE;
    }
}

void zap::Shader::use() const noexcept
{
    glUseProgram(_program);
}

/**
* private
*/

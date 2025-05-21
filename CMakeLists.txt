cmake_minimum_required(VERSION 3.16)
project(zappy VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

########################################
# INFO: enable multithreading for build
########################################
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

########################################
# INFO: CMake cache management for faster builds
########################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

########################################
# NOTE: GLFW configuration
########################################
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(external/glfw EXCLUDE_FROM_ALL)

########################################
# NOTE: GLM configuration
########################################
option(GLM_TEST_ENABLE OFF)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

########################################
# NOTE: GLAD configuration
########################################
set(GLAD_INSTALL OFF)
add_subdirectory(external/glad/cmake EXCLUDE_FROM_ALL)
glad_add_library(glad STATIC API gl:core=3.3)

########################################
# NOTE: Assimp configuration
########################################
add_subdirectory(external/assimp EXCLUDE_FROM_ALL)

########################################
# NOTE: Zappy graphical API
########################################
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(zappy ${SOURCES})
target_include_directories(zappy PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_BINARY_DIR}/gladsources/glad/include
)
target_link_libraries(zappy PRIVATE
    glfw
    glad
    glm::glm
    assimp::assimp
)
# target_compile_options(zappy PRIVATE
#     # INFO: classic yutsu warnings
#     -Wall
#     -Wextra
#     -Werror
#     -pedantic
#
#     # INFO: type safety & conversions
#     -Wconversion
#     -Wsign-conversion
#     -Wfloat-equal # << WARN: PURE HATE flag lol
#
#     # INFO: code correctness
#     -Wshadow
#     -Wnull-dereference
#     -Wundef
#     -Wuninitialized
#     -Winit-self
#     -Wredundant-decls
#
#     # INFO: code hygiene
#     -Wcast-align
#     -Wcast-qual
#     -Wmissing-declarations
#     -Woverloaded-virtual
#     -Wnon-virtual-dtor
#
#     # INFO: logic bugs & bad practices
#     # -Wduplicated-cond << not on clang
#     # -Wduplicated-branches << not on clang
#     # -Wlogical-op << not on clang
#     -Wswitch-default
#     # -Wswitch-enum << commented because i dont think this flag is pertinent (we have default: break...)
#     # -Wuseless-cast << not on clang
#
#     # INFO: prevent common portability issues
#     -Wdouble-promotion
#     -Wformat=2
#     -Wwrite-strings
# )

# << NOTE: this is a workaround bc glad compilation is strange so we assure that it is compiled BEFORE zappy
add_dependencies(zappy glad)

########################################
# NOTE: debug
########################################
option(ENABLE_DEBUG "Enable debug macros and flags" OFF)

if(ENABLE_DEBUG)
    target_compile_definitions(zappy PRIVATE DEBUG=1)
endif()


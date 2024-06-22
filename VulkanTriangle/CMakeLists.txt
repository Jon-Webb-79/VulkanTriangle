cmake_minimum_required(VERSION 3.29.6)
project(VulkanTriangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include ExternalProject module to manage external dependencies
include(ExternalProject)

# Define GLFW as an external project
ExternalProject_Add(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
    CMAKE_ARGS -DGLFW_BUILD_EXAMPLES=OFF
               -DGLFW_BUILD_TESTS=OFF
               -DGLFW_BUILD_DOCS=OFF
               -DGLFW_BUILD_INSTALL=OFF
               -DGLFW_BUILD_WAYLAND=OFF
               -DGLFW_BUILD_X11=ON
    PREFIX ${CMAKE_BINARY_DIR}/glfw
    INSTALL_COMMAND ""
)

# Find the Vulkan package
find_package(Vulkan REQUIRED)

# Find the glslangValidator tool
find_program(GLSLANG_VALIDATOR glslangValidator HINTS "$ENV{VULKAN_SDK}/bin" REQUIRED)

# Check glslangValidator version
execute_process(
    COMMAND ${GLSLANG_VALIDATOR} --version
    OUTPUT_VARIABLE GLSLANG_VALIDATOR_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Found glslangValidator: ${GLSLANG_VALIDATOR}")
message(STATUS "glslangValidator version: ${GLSLANG_VALIDATOR_VERSION}")

# Define the executable
add_executable(VulkanTriangle 
               main.cpp
               window.cpp
               application.cpp
               validation_layers.cpp
)

# Include GLFW and Vulkan directories
ExternalProject_Get_Property(glfw source_dir binary_dir)
target_include_directories(VulkanTriangle PRIVATE ${source_dir}/include)
target_include_directories(VulkanTriangle PRIVATE ${Vulkan_INCLUDE_DIRS})

# Link the GLFW and Vulkan libraries and add the necessary linker flags
add_dependencies(VulkanTriangle glfw)
target_link_libraries(VulkanTriangle PRIVATE ${binary_dir}/src/libglfw3.a Vulkan::Vulkan dl pthread X11 Xxf86vm Xrandr Xi)

# Set the output directory for the executable
set_target_properties(VulkanTriangle PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Additional flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native -fPIE")

# Set debug-specific compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wpedantic -g")

# Set release-specific compiler flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror -Wpedantic -O2")


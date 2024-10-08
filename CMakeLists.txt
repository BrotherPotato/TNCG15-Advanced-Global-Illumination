#CMakeLists
cmake_minimum_required(VERSION 3.13.0...3.20)
project(TNCG15-Raytracer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

# Collect all source files in the 'src' and 'include' directories
file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "include/*.h")

add_executable(Raytracing ${SOURCES} ${HEADERS})
# target_include_directories(Raytracing PUBLIC include ext/stb)

enable_warnings(Raytracing)

# Add glm to project and source 
target_include_directories(Raytracing PUBLIC ${PROJECT_SOURCE_DIR}/ext/glm ${PROJECT_SOURCE_DIR})

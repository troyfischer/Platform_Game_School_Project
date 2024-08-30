# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set the target architecture for Apple Silicon
if(APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    set(CMAKE_OSX_ARCHITECTURES "arm64")  # Ensures CMake builds for Apple Silicon
endif()


# Set the project name
project(Platformer)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add Homebrew library paths
set(CMAKE_PREFIX_PATH "/opt/homebrew")

include_directories(include)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Verify and print the include directories
message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

# Use pkg-config to find SDL2_mixer
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_MIXER REQUIRED sdl2_mixer)

# Verify and print the include directories
message(STATUS "SDL2_mixer include dirs: ${SDL2_MIXER_INCLUDE_DIRS}")
message(STATUS "SDL2_mixer libraries: ${SDL2_MIXER_LIBRARIES}")

# Use pkg-config to find SDL2_image
pkg_check_modules(SDL2_IMAGE REQUIRED sdl2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Use pkg-config to find SDL2_ttf
pkg_check_modules(SDL2_TTF REQUIRED sdl2_ttf)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Link SDL2 and its modules with the correct linker flags
link_directories(${SDL2_MIXER_LIBRARY_DIRS} ${SDL2_IMAGE_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable (make sure the executable name matches the target)
add_executable(Platformer ${SOURCES})

# Link SDL2 to your target
target_link_libraries(Platformer ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

set(CMAKE_CXX_STANDARD 11)  # 或者更高版本，如 17 或 20
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(/opt/homebrew/Cellar/raylib/5.5/include)

link_directories(/opt/homebrew/Cellar/raylib/5.5/lib)

file(GLOB SOURCE "*.cpp")

add_executable(exp main.cpp ${SOURCE} cal.cpp)

target_link_libraries(exp raylib)
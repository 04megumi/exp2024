include_directories(${CMAKE_SOURCE_DIR}/include)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE "*.cpp")

add_executable(exp main.cpp ${SOURCE})

target_link_libraries(exp sfml-graphics sfml-window sfml-system)
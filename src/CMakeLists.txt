include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system REQUIRED)

file(GLOB SOURCE "*.cpp")

add_executable(exp main.cpp ${SOURCE})

target_link_libraries(exp sfml-graphics sfml-window sfml-system)
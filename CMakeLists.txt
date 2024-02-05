cmake_minimum_required(VERSION 3.20)
project(GE01004_ass_0)

set(CMAKE_CXX_STANDARD 17)

# find CGAL
find_package(CGAL REQUIRED)

add_executable(GE01004_ass_0 main.cpp)

# link CGAL libraries
target_link_libraries(GE01004_ass_0 CGAL::CGAL)



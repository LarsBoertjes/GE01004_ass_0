cmake_minimum_required(VERSION 3.20)
project(GE01004_ass_0)

set(CMAKE_CXX_STANDARD 17)

# Find CGAL
find_package(CGAL REQUIRED COMPONENTS Qt5)
message("CGAL Version: ${CGAL_VERSION}")

add_executable(GE01004_ass_0 main.cpp)
# Link with CGAL libraries and Basic Viewer
target_link_libraries(GE01004_ass_0 CGAL::CGAL)


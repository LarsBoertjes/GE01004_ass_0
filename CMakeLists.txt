cmake_minimum_required(VERSION 3.20)
project(GE01004_ass_0)

set(CMAKE_CXX_STANDARD 17)

# Find CGAL
find_package(CGAL REQUIRED COMPONENTS Qt5)

# CGAL_Qt5 should be found as well, as it's needed for CGAL::CGAL_Basic_viewer
find_package(CGAL COMPONENTS Qt5)

if (TARGET CGAL::CGAL_Qt5)
    add_definitions(-DCGAL_USE_BASIC_VIEWER)
    add_executable(GE01004_ass_0 main.cpp)
    # Link with CGAL libraries and Basic Viewer
    target_link_libraries(GE01004_ass_0 CGAL::CGAL CGAL::CGAL_Basic_viewer)
else()
    message(STATUS "NOTICE: This demo requires the CGAL Qt5 library, and will not be compiled.")
endif()

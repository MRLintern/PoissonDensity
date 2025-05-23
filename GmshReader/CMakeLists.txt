cmake_minimum_required(VERSION 3.18.3)

set(PROJECT_NAME GmshReader)

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)

# static library creation
add_library(GmshReader STATIC

	GmshReader.cpp
	GmshReader.hpp

)

# link Eigen library to the GmshReacer
target_link_libraries(GmshReader PUBLIC Eigen3::Eigen)

# executable
add_executable(main mainGmshReader.cpp)

# link GmshReader library to the executable
target_link_libraries(main PRIVATE GmshReader)

# include header files
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})




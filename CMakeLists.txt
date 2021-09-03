cmake_minimum_required(VERSION 3.11.3)
project(noise-removal)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE "Debug") #to be able to reading binary symbols in ubuntu, source: https://dominoc925.blogspot.com/2015/12/no-debugging-symbols-found-in-gdb-after.html 
SET(OpenCV_DIR lib/opencv)

file(GLOB project_SRCS src/*.cpp)
add_executable(noise-removal ${project_SRCS})

find_package(OpenCV 4.5.3 REQUIRED  PATHS lib/opencv)

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( 
    noise-removal
     ${OpenCV_LIBS}
)

target_include_directories(
    noise-removal
     PRIVATE ${OpenCV_INCLUDE_DIRS} 
)
cmake_minimum_required(VERSION 3.11.3)
project(image-bluring)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE "Debug") #to be able to reading binary symbols in ubuntu, source: https://dominoc925.blogspot.com/2015/12/no-debugging-symbols-found-in-gdb-after.html 
SET(OpenCV_DIR lib/opencv)

file(GLOB project_SRCS src/*.cpp)
add_executable(image-bluring ${project_SRCS})

find_package(OpenCV REQUIRED  PATHS lib/opencv)
find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( 
    image-bluring
    ${wxWidgets_LIBRARIES}
     ${OpenCV_LIBS}
)

target_include_directories(
    image-bluring
    PRIVATE ${wxWidgets_INCLUDE_DIRS}
    PRIVATE ${OpenCV_INCLUDE_DIRS} 
)
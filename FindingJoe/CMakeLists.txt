cmake_minimum_required(VERSION 3.5)
project(FindingJoe)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(OpenCV_FOUND 1)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)
link_libraries(-pthread)


add_executable(FindingJoe ${SOURCE_FILES})

target_link_libraries(FindingJoe ${OpenCV_LIBS})



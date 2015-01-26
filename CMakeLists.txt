cmake_minimum_required(VERSION 2.8)
project(SkinDetector)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Find external libraries
find_package(OpenCV REQUIRED)
find_package(OpenMP)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -O0  -Wall -Wextra -Wunused-variable -DDEBUG -D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g  -Wall -Wextra -Wunused-variable -DDEBUG -D_DEBUG")

if(OPENMP_FOUND)
    message("OpenMP found")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -O3  -Wall -Wextra -Wunused-variable  -g -msse2 -msse3 -msse4 -ffast-math")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O3 -Wall -Wextra -Wunused-variable -g -msse2 -msse3 -msse4 -ffast-math")
else(OPENMP_FOUND)
    message("OpenMP not found")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3 -Wno-unknown-pragmas -Wunused-variable -g -msse2 -msse3 -msse4 -ffast-math")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wno-unknown-pragmas -Wunused-variable -g -msse2 -msse3 -msse4 -ffast-math")
endif(OPENMP_FOUND)

ADD_DEFINITIONS(-DDEBUG -ggdb -O3 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -ffast-math -fbranch-probabilities)


INCLUDE_DIRECTORIES("src/")
set(SRCS
    src/mainApp.cpp
    src/skindetector.cpp
)

ADD_EXECUTABLE(
  run_demo
  run_demo.cpp
  ${SRCS}
)

TARGET_LINK_LIBRARIES(
  run_demo
  ${OpenCV_LIBS}
)

cmake_minimum_required(VERSION 4.3.1)
project("RavenBalancer" CXX)

set(CMAKE_CXX_STANDARD 23)
file(GLOB SOURCE_FILES *.cpp *.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

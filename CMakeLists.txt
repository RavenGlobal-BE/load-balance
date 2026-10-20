cmake_minimum_required(VERSION 4.3.1)
project("RavenBalancer" CXX)

set(CMAKE_CXX_STANDARD 23)
file(GLOB SOURCE_FILES *.cpp *.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

option(ENABLE_SANITIZERS "Build with AddressSanitizer and UBSan" OFF)

if(ENABLE_SANITIZERS)
    target_compile_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -g
    )
    target_link_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address,undefined
    )
endif()
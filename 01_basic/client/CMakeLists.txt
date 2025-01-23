cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(LearnAsio_01_Basic_Client)

# C++ 표준 설정 (C++11, C++14, C++17 등 선택)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# fmt
include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

# boost
find_package(Boost REQUIRED COMPONENTS filesystem thread system)

include_directories(${Boost_INCLUDE_DIRS})

# 실행 파일 생성
add_executable(${PROJECT_NAME} client.cpp)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY})

# 빌드 디렉토리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 컴파일러 경고 설정
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

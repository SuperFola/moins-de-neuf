cmake_minimum_required(VERSION 3.8)

project(moinsDeNeuf CXX)

file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# including content of project

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# setting up project properties

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# building exe

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
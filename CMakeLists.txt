cmake_minimum_required(VERSION 3.8)

project(moinsDeNeuf CXX)

file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# including content of project
include_directories(${PROJECT_SOURCE_DIR}/include)

# building exe
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# setting up project properties
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
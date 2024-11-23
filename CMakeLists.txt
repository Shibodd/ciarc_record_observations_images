cmake_minimum_required (VERSION 3.11)

project (melvin_logger)

add_compile_options (-Wall -Wextra -Wpedantic -O3)

SET (CMAKE_CXX_STANDARD 20)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchContent)
FetchContent_Declare (glaze GIT_REPOSITORY https://github.com/stephenberry/glaze.git
                           GIT_TAG main
                           GIT_SHALLOW TRUE)
FetchContent_GetProperties(glaze)
if(NOT glaze_POPULATED)
  FetchContent_Populate(glaze)
  add_subdirectory(${glaze_SOURCE_DIR} ${glaze_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

find_package (ciarcpp REQUIRED)

add_executable (melvin_logger logger.cpp serialize_observation.cpp)
target_link_libraries (melvin_logger PRIVATE ciarcpp)
target_link_libraries (melvin_logger PRIVATE glaze::glaze)

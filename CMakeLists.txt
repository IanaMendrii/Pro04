cmake_minimum_required(VERSION 3.8)

project(Pro04)
set(CMAKE_BUILD_TYPE Release)
set(SRC_DIR src)

set(EXAMPLE_SRC ${SRC_DIR}/main.cpp
                ${SRC_DIR}/Config.cpp
                ${SRC_DIR}/ParseConfig.cpp
				${SRC_DIR}/KeyValuePair.cpp
				${SRC_DIR}/Sections.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${EXAMPLE_SRC})

set_property(TARGET Pro04 PROPERTY CXX_STANDARD 11)
set_property(TARGET Pro04 PROPERTY CXX_STANDARD_REQUIRED ON)
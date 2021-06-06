
cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 17)

project ("Python CPP Object API")

set(INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    "D:\\dev\\python\\python395\\include"
)

include_directories(${INCLUDES})

set(PYTHON_LIB_FILES "D:/dev/python/python395/libs/python39.lib")

set(SOURCE
    source/Object.cpp
)

enable_testing()

add_executable(Unit_Object ${SOURCE} ${PROJECT_SOURCE_DIR}/test/u_Object.cpp)
add_test("Py::Object construction" Unit_Object "1")

target_link_libraries(
    Unit_Object
    ${PYTHON_LIB_FILES}
    )
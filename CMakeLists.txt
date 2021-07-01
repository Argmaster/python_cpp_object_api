
cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 20)

project ("Python CPP Object API")

set(INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps/python/include
)
set(PYTHON_LIB_FILES ${PROJECT_SOURCE_DIR}/deps/python/libs/python39.lib)

include_directories(${INCLUDES})
link_libraries(${PYTHON_LIB_FILES})

file(GLOB GLOB_SOURCES
    source/*.cpp
)

enable_testing()

add_executable(Unit_Object ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Object.cpp)
add_test("Py::Object construction" Unit_Object "1")
add_test("Py::Object casts" Unit_Object "2")
add_test("Py::Object methods" Unit_Object "3")

add_executable(Unit_Str ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Str.cpp)
add_test("Py::Str construction" Unit_Str "1")
add_test("Py::Str encode" Unit_Str "2")
add_test("Py::Str methods" Unit_Str "3")

add_executable(Unit_Bytes ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Bytes.cpp)
add_test("Py::Bytes construction" Unit_Bytes "1")
add_test("Py::Bytes methods" Unit_Bytes "2")

add_executable(Unit_Tuple ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Tuple.cpp)
add_test("Py::Tuple construction" Unit_Tuple "1")
add_test("Py::Tuple methods" Unit_Tuple "2")

add_executable(Unit_List ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_List.cpp)
add_test("Py::List construction" Unit_List "1")
add_test("Py::List methods" Unit_List "2")

add_executable(Unit_Dict ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Dict.cpp)
add_test("Py::Dict construction" Unit_Dict "1")
add_test("Py::Dict methods" Unit_Dict "2")

add_executable(Unit_Module ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Module.cpp)
add_test("Py::Module construction" Unit_Dict "1")
add_test("Py::Module methods" Unit_Dict "2")

add_executable(Unit_Function ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/u_Function.cpp)
add_test("Py::Function construction" Unit_Function "1")
add_test("Py::Function methods" Unit_Function "2")
cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 20)

project (python_cpp_object_api)

set(INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps/python/include
)
set(PYTHON_LIB_FILES
    ${PROJECT_SOURCE_DIR}/deps/python/libs/python39.lib
)
include_directories(${INCLUDES})
link_libraries(${PYTHON_LIB_FILES})

file(GLOB GLOB_SOURCES source/*.cpp)
add_library(${PROJECT_NAME} STATIC ${GLOB_SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${INCLUDES}
)
target_link_libraries(
    ${PROJECT_NAME}
    ${PYTHON_LIB_FILES}
)

if (NOT (python_cpp_object_api_OMIT_TESTS STREQUAL YES))
    enable_testing()

    add_executable(Unit_Bool ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Bool.cpp)
    # add_test("Py::Bool from c bool" Unit_Object "1")

    add_executable(Unit_ByteArray ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_ByteArray.cpp)
    # add_test("Py::ByteArray" Unit_ByteArray "1")

    add_executable(Unit_Bytes ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Bytes.cpp)
    add_test("Py::Bytes construction" Unit_Bytes "1")
    add_test("Py::Bytes methods" Unit_Bytes "2")

    add_executable(Unit_Complex ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Complex.cpp)
    #add_test("Py::Complex" Unit_Complex "1")

    add_executable(Unit_Dict ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Dict.cpp)
    add_test("Py::Dict construction" Unit_Dict "1")
    add_test("Py::Dict methods" Unit_Dict "2")

    add_executable(Unit_Exception ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Exception.cpp)
    # add_test("Py::Exception" Unit_Exception "1")

    add_executable(Unit_Float ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Float.cpp)
    # add_test("Py::Float" Unit_Float "1")

    add_executable(Unit_FrozenSet ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_FrozenSet.cpp)
    # add_test("Py::FrozenSet" Unit_FrozenSet "1")

    add_executable(Unit_Function ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Function.cpp)
    add_test("Py::Function construction" Unit_Function "1")
    add_test("Py::Function methods" Unit_Function "2")

    add_executable(Unit_List ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_List.cpp)
    add_test("Py::List from PyObject* construction" Unit_List "1")
    add_test("Py::List from initializer list construction" Unit_List "2")
    add_test("Py::List from size construction" Unit_List "3")
    add_test("Py::List method GetItem" Unit_List "4")
    add_test("Py::List method SetItem" Unit_List "5")
    add_test("Py::List method GetSlice" Unit_List "6")
    add_test("Py::List method SetSlice" Unit_List "7")
    add_test("Py::List method Append" Unit_List "8")
    add_test("Py::List method Insert" Unit_List "9")
    add_test("Py::List method Sort" Unit_List "10")
    add_test("Py::List method Reverse" Unit_List "11")
    add_test("Py::List method ToTuple" Unit_List "12")
    add_test("Py::List method Contains" Unit_List "13")
    add_test("Py::List method Count" Unit_List "14")
    add_test("Py::List method Index" Unit_List "15")

    add_executable(Unit_Long ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Long.cpp)
    # add_test("Py::Long" Unit_Long "1")

    add_executable(Unit_Mapping ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Mapping.cpp)
    # add_test("Py::Mapping" Unit_Mapping "1")

    add_executable(Unit_Module ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Module.cpp)
    add_test("Py::Module construction" Unit_Dict "1")
    add_test("Py::Module methods" Unit_Dict "2")

    add_executable(Unit_Object ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Object.cpp)
    add_test("Py::Object from PyObject*" Unit_Object "1")
    add_test("Py::Object copy & move" Unit_Object "2")
    add_test("Py::Object reference count" Unit_Object "3")
    add_test("Py::Object As<>() type cast" Unit_Object "4")
    add_test("Py::Object Is checks" Unit_Object "5")
    add_test("Py::Object Attr & Item methods" Unit_Object "6")
    add_test("Py::Object Comprisons" Unit_Object "7")
    add_test("Py::Object Numerical operators" Unit_Object "8")

    add_executable(Unit_Set ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Set.cpp)
    # add_test("Py::Set" Unit_Set "1")

    add_executable(Unit_Str ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Str.cpp)
    add_test("Py::Str construction" Unit_Str "1")
    add_test("Py::Str encode" Unit_Str "2")
    add_test("Py::Str methods" Unit_Str "3")

    add_executable(Unit_Tuple ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Unit_Tuple.cpp)
    add_test("Py::Tuple construction" Unit_Tuple "1")
    add_test("Py::Tuple methods" Unit_Tuple "2")

    # Integration tests
    add_executable(Integ_Core ${GLOB_SOURCES} ${PROJECT_SOURCE_DIR}/test/Integ_Core.cpp)
    add_test("Py::Core integrate" Integ_Core)
endif()
#pragma once
#ifdef _DEBUG
#undef _DEBUG
#define _DEBUG_MARKER 1
#endif
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#ifdef _DEBUG_MARKER
#undef _DEBUG_MARKER
#define _DEBUG 1
#endif
#include <iostream>
#include <string>


namespace Py
{
    class __WrapperInterface
    {
    protected:
        PyObject* m_ref;
        /// Default constructor only for inner usage
        __WrapperInterface() : m_ref(nullptr) {}
        /// Assume that pointer given is a new reference
        __WrapperInterface(PyObject* py_object)
            : m_ref(py_object) {
            printf("New object\n");
        }
    public:
        /// Copies reference contained by Str, refcount is incremented
        __WrapperInterface(const __WrapperInterface& moved_object)
            : m_ref(moved_object.m_ref) {
            Py_XINCREF(moved_object.m_ref);
        }
        /// Moves reference contained by Str, assumes new reference
        __WrapperInterface(__WrapperInterface&& moved_object)
            : m_ref(moved_object.m_ref) {
            moved_object.m_ref = nullptr;
        }
        /// When dies always decrefs underlying PyObject pointer (null-safe)
        virtual ~__WrapperInterface() {
            Py_XDECREF(m_ref);
        }
        /// Cast to polimorphic PyObject*
        operator PyObject* () { return m_ref; }
        /// Static cast to another wrapper type
        template<class cast_type>
        cast_type           As() { return cast_type::FromOld(m_ref); }
        // Explicit shortcut for null test
        inline bool         IsNull() const { return m_ref == NULL; }
        // Expilcit shortcut for not null test
        inline bool         IsNotNull() const { return m_ref != NULL; }
        /// Acquire reference count of underlying PyObject
        inline Py_ssize_t   RefC() const { return Py_REFCNT(m_ref); }
        /* -------------------------------------------------------------------------- */
        /*                            Type checks shortcuts                           */
        /* -------------------------------------------------------------------------- */
        inline bool         IsLong() { return PyLong_CheckExact(m_ref); }
        inline bool         IsFloat() { return PyFloat_CheckExact(m_ref); }
        inline bool         IsComplex() { return PyComplex_CheckExact(m_ref); }
        inline bool         IsBool() { return PyBool_Check(m_ref); }
        inline bool         IsStr() { return PyUnicode_CheckExact(m_ref); }
        inline bool         IsBytes() { return PyBytes_CheckExact(m_ref); }
        inline bool         IsByteArray() { return PyByteArray_CheckExact(m_ref); }
        inline bool         IsList() { return PyList_CheckExact(m_ref); }
        inline bool         IsTuple() { return PyTuple_CheckExact(m_ref); }
        inline bool         IsDict() { return PyDict_CheckExact(m_ref); }
        inline bool         IsSet() { return PyAnySet_CheckExact(m_ref); }
        inline bool         IsFrozenSet() { return PyFrozenSet_CheckExact(m_ref); }
    };
}


#include "Object.hh"
#include "Long.hh"
#include "Float.hh"
#include "Complex.hh"
#include "Bool.hh"
#include "Str.hh"
#include "Bytes.hh"
#include "ByteArray.hh"
#include "List.hh"
#include "Tuple.hh"
#include "Dict.hh"
#include "Set.hh"
#include "FrozenSet.hh"


#define __LOG(info) std::cout << info << std::cout;
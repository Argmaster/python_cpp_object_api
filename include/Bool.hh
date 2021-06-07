#pragma once
#include "Common.hh"

namespace Py
{
    struct Bool : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        // Custom class constuctor from C bool to Python Bool
        Bool(bool _bool) {
            m_ref = PyBool_FromLong(_bool);
        }
        /// Construct Bool out of New PyObject Reference
        static Bool         FromNew(PyObject* py_new_ref) { return Bool(py_new_ref); } // ! new reference construction
        /// Construct Bool out of Borrowed PyObject Reference
        static Bool         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Bool(py_weak_ref); } // ? borrowed reference construction
        operator bool() const { return PyObject_IsTrue(m_ref); }
    };
}
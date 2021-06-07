#pragma once
#include "Common.hh"

namespace Py
{
    struct Long : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        // Custom class constuctor from C bool to Python Bool
        Long(long _long) {
            m_ref = PyLong_FromLong(_long);
        }
        /// Construct Long out of New PyObject Reference
        static Long         FromNew(PyObject* py_new_ref) { return Long(py_new_ref); } // ! new reference construction
        /// Construct Long out of Borrowed PyObject Reference
        static Long         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Long(py_weak_ref); } // ? borrowed reference construction

    };
}
#pragma once
#include "Common.hh"

namespace Py
{
    struct Float : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        // Custom class constuctor from C bool to Python Bool
        static Float New(long double _value) {
            return Float::FromNew(PyFloat_FromDouble(_value));
        }
        /// Construct Float out of New PyObject Reference
        static Float         FromNew(PyObject* py_new_ref) { return Float(py_new_ref); } // ! new reference construction
        /// Construct Float out of Borrowed PyObject Reference
        static Float         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Float(py_weak_ref); } // ? borrowed reference construction

    };
}
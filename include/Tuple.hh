#pragma once
#include "Common.hh"

namespace Py
{
    struct Tuple : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;

        /// Construct Tuple out of New PyObject Reference
        static Tuple         FromNew(PyObject* py_new_ref) { return Tuple(py_new_ref); } // ! new reference construction
        /// Construct Tuple out of Borrowed PyObject Reference
        static Tuple         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Tuple(py_weak_ref); } // ? borrowed reference construction
    };
}
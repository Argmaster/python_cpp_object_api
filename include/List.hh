#pragma once
#include "Common.hh"

namespace Py
{
    struct List : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;

        /// Construct List out of New PyObject Reference
        static List         FromNew(PyObject* py_new_ref) { return List(py_new_ref); } // ! new reference construction
        /// Construct List out of Borrowed PyObject Reference
        static List         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return List(py_weak_ref); } // ? borrowed reference construction

    };
}
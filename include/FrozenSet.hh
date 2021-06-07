#pragma once
#include "Common.hh"

namespace Py
{
    struct FrozenSet : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;

        /// Construct FrozenSet out of New PyObject Reference
        static FrozenSet         FromNew(PyObject* py_new_ref) { return FrozenSet(py_new_ref); } // ! new reference construction
        /// Construct FrozenSet out of Borrowed PyObject Reference
        static FrozenSet         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return FrozenSet(py_weak_ref); } // ? borrowed reference construction

    };
}
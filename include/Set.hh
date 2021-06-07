#include "Common.hh"

namespace Py
{
    struct Set : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;

        /// Construct Set out of New PyObject Reference
        static Set         FromNew(PyObject* py_new_ref) { return Set(py_new_ref); } // ! new reference construction
        /// Construct Set out of Borrowed PyObject Reference
        static Set         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Set(py_weak_ref); } // ? borrowed reference construction

    };
}
#include "Common.hh"

namespace Py
{
    struct Dict : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        /// Construct Dict out of New PyObject Reference
        static Dict         FromNew(PyObject* py_new_ref) { return Dict(py_new_ref); } // ! new reference construction
        /// Construct Dict out of Borrowed PyObject Reference
        static Dict         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Dict(py_weak_ref); } // ? borrowed reference construction

    };
}
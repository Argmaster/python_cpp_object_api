#include "Common.hh"

namespace Py
{
    struct Complex : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        // Custom class constuctor from C bool to Python Bool
        static Complex New(long double _real, long double _imag) {
            return Complex::FromNew(PyComplex_FromDoubles(_real, _imag));
        }
        /// Construct Complex out of New PyObject Reference
        static Complex         FromNew(PyObject* py_new_ref) { return Complex(py_new_ref); } // ! new reference construction
        /// Construct Complex out of Borrowed PyObject Reference
        static Complex         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Complex(py_weak_ref); } // ? borrowed reference construction

    };
}
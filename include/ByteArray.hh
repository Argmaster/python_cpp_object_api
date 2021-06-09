#include "Common.hh"

namespace Py
{
    struct ByteArray : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        // Custom class constuctor from C bool to Python Bool
        static ByteArray New(const std::string& _string) {
            return ByteArray::FromNew(PyByteArray_FromStringAndSize(_string.c_str(), _string.length()));
        }
        /// Construct ByteArray out of New PyObject Reference
        static ByteArray         FromNew(PyObject* py_new_ref) { return ByteArray(py_new_ref); } // ! new reference construction
        /// Construct ByteArray out of Borrowed PyObject Reference
        static ByteArray         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return ByteArray(py_weak_ref); } // ? borrowed reference construction

    };
}
#pragma once
#include "Common.hh"

namespace Py
{
    struct Bytes : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        // Custom class constuctor from C bool to Python Bool
        Bytes(const std::string& _string) {
            m_ref = PyBytes_FromStringAndSize(_string.c_str(), _string.length());
        }
        /// Construct Bytes out of New PyObject Reference
        static Bytes         FromNew(PyObject* py_new_ref) { return Bytes(py_new_ref); } // ! new reference construction
        /// Construct Bytes out of Borrowed PyObject Reference
        static Bytes         FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Bytes(py_weak_ref); } // ? borrowed reference construction

    };
}
#pragma once
#include "Common.hh"


namespace Py
{
    struct Str : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        Str(const std::string& _string) {
            m_ref = PyUnicode_FromStringAndSize(_string.c_str(), _string.length());
        }
        /// Construct Str out of New PyObject Reference
        static Str          FromNew(PyObject* py_new_ref) { return { py_new_ref }; } // ! new reference construction
        /// Construct Str out of Borrowed PyObject Reference
        static Str          FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return { py_weak_ref }; } // ? borrowed reference construction
        operator Object () { return Object::FromOld(m_ref); }
        operator Long () { return Long::FromOld(m_ref); }
        operator Float () { return Float::FromOld(m_ref); }
        operator Complex () { return Complex::FromOld(m_ref); }
        operator Bool () { return Bool::FromOld(m_ref); }
        // operator Str () { return Str::FromOld(m_ref); }
        operator Bytes () { return Bytes::FromOld(m_ref); }
        operator ByteArray () { return ByteArray::FromOld(m_ref); }
        operator List () { return List::FromOld(m_ref); }
        operator Tuple () { return Tuple::FromOld(m_ref); }
        operator Dict () { return Dict::FromOld(m_ref); }
        operator Set () { return Set::FromOld(m_ref); }
        operator FrozenSet () { return FrozenSet::FromOld(m_ref); }
        inline const char*  AsUTF8() { return PyUnicode_AsUTF8(m_ref); }
    };
}
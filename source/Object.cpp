#include "Object.hh"


namespace Py
{
    /* -------------------------------------------------------------------------- */
    /*                 Implicit dynamic casts among wrapper types                 */
    /* -------------------------------------------------------------------------- */
    //Object::operator Object () { return Object::FromOld(m_ref); }
    Object::operator Long () { return Long::FromOld(m_ref); }
    Object::operator Float () { return Float::FromOld(m_ref); }
    Object::operator Complex () { return Complex::FromOld(m_ref); }
    Object::operator Bool () { return Bool::FromOld(m_ref); }
    Object::operator Str () { return Str::FromOld(m_ref); }
    Object::operator Bytes () { return Bytes::FromOld(m_ref); }
    Object::operator ByteArray () { return ByteArray::FromOld(m_ref); }
    Object::operator List () { return List::FromOld(m_ref); }
    Object::operator Tuple () { return Tuple::FromOld(m_ref); }
    Object::operator Dict () { return Dict::FromOld(m_ref); }
    Object::operator Set () { return Set::FromOld(m_ref); }
    Object::operator FrozenSet () { return FrozenSet::FromOld(m_ref); }
    /* -------------------------------------------------------------------------- */
    /*                          Getters, setter, deleters                         */
    /* -------------------------------------------------------------------------- */
    bool            Object::HasAttr(Str attr_name) const {
        auto result = PyObject_HasAttr(m_ref, attr_name.GetRef());
        Py_XDECREF(attr_name);
        return result;
    }
    Object          Object::GetAttr(Str attr_name) const {
        return FromNew(PyObject_GetAttr(m_ref, attr_name));
    }
    int             Object::SetAttr(Str attr_name, PyObject* value) const {
        return PyObject_SetAttr(m_ref, attr_name, value);
    }
    int             Object::DelAttr(Str attr_name) const {
        return PyObject_DelAttr(m_ref, attr_name);
    }
    Object          Object::GetItem(Str attr_name) const {
        return FromNew(PyObject_GetItem(m_ref, attr_name));
    }
    int             Object::SetItem(Str attr_name, PyObject* value) const {
        return PyObject_SetAttr(m_ref, attr_name, value);
    }
    int             Object::DelItem(Str attr_name) const {
        return PyObject_DelAttr(m_ref, attr_name);
    }
    /* -------------------------------------------------------------------------- */
    /*                                 Comparisons                                */
    /* -------------------------------------------------------------------------- */
    Bool            Object::LT(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Bool            Object::operator < (Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Bool            Object::LE(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Bool            Object::operator <= (Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Bool            Object::EQ(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Object::operator == (Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Object::NE(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Bool            Object::operator != (Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Bool            Object::GT(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Bool            Object::operator > (Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Bool            Object::GE(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_GE)); }
    Bool            Object::operator >= (Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_GE)); }
    /* -------------------------------------------------------------------------- */
    /*                       Type operations and conversions                      */
    /* -------------------------------------------------------------------------- */
    Str             Object::Repr() const { return Str::FromNew(PyObject_Repr(m_ref)); }
    Str             Object::ASCII() const { return Str::FromNew(PyObject_ASCII(m_ref)); }
    Str             Object::ToStr() const { return Str::FromNew(PyObject_Str(m_ref)); }
    Str             Object::ToBytes() const { return Str::FromNew(PyObject_Bytes(m_ref)); }
    Py_hash_t       Object::Hash() const { return PyObject_Hash(m_ref); }
    bool            Object::IsTrue() const { return PyObject_IsTrue(m_ref); }
    bool            Object::Not() const { return PyObject_Not(m_ref); }
    Py_ssize_t      Object::Size() const { return PyObject_Size(m_ref); }
    Py_ssize_t      Object::Length() const { return PyObject_Length(m_ref); }

}
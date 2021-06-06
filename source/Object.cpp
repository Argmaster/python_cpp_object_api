#include "Object.hh"


namespace Py
{
    /* -------------------------------------------------------------------------- */
    /*                          Getters, setter, deleters                         */
    /* -------------------------------------------------------------------------- */
    bool            Object::HasAttr(Str attr_name) const {
        return PyObject_HasAttr(m_ref, attr_name);
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
    Object          Object::GetItem(Object attr_name) const {
        return FromNew(PyObject_GetItem(m_ref, attr_name));
    }
    int             Object::SetItem(Object attr_name, PyObject* value) const {
        return PyObject_SetAttr(m_ref, attr_name, value);
    }
    int             Object::DelItem(Object attr_name) const {
        return PyObject_DelAttr(m_ref, attr_name);
    }
    /* -------------------------------------------------------------------------- */
    /*                                 Comparisons                                */
    /* -------------------------------------------------------------------------- */
    Object          Object::LT(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Object          Object::LE(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Object          Object::EQ(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Object          Object::NE(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Object          Object::GT(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Object          Object::GE(Object other) const { return Object::FromNew(PyObject_RichCompare(m_ref, other, Py_GE)); }
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
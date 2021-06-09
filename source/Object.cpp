#include "Object.hh"


namespace Py
{
    /* -------------------------------------------------------------------------- */
    /*                 Implicit dynamic casts among wrapper types                 */
    /* -------------------------------------------------------------------------- */
    //Object::operator Object () { return Object::FromOld(m_ref); }
    Object::operator Long () { return FromOld<Long>(m_ref); }
    Object::operator Float () { return FromOld<Float>(m_ref); }
    Object::operator Complex () { return FromOld<Complex>(m_ref); }
    Object::operator Bool () { return FromOld<Bool>(m_ref); }
    Object::operator Str () { return FromOld<Str>(m_ref); }
    Object::operator Bytes () { return FromOld<Bytes>(m_ref); }
    Object::operator ByteArray () { return FromOld<ByteArray>(m_ref); }
    Object::operator List () { return FromOld<List>(m_ref); }
    Object::operator Tuple () { return FromOld<Tuple>(m_ref); }
    Object::operator Dict () { return FromOld<Dict>(m_ref); }
    Object::operator Set () { return FromOld<Set>(m_ref); }
    Object::operator FrozenSet () { return FromOld<FrozenSet>(m_ref); }
    /* -------------------------------------------------------------------------- */
    /*                          Getters, setter, deleters                         */
    /* -------------------------------------------------------------------------- */
    bool            Object::HasAttr(Str attr_name) const {
        //Py_XDECREF(attr_name);
        return PyObject_HasAttr(m_ref, attr_name);;
    }
    Object          Object::GetAttr(Str attr_name) const {
        return PyObject_GetAttr(m_ref, attr_name);
    }
    int             Object::SetAttr(Str attr_name, PyObject* value) const {
        return PyObject_SetAttr(m_ref, attr_name, value);
    }
    int             Object::DelAttr(Str attr_name) const {
        return PyObject_DelAttr(m_ref, attr_name);
    }
    Object          Object::GetItem(Str attr_name) const {
        return PyObject_GetItem(m_ref, attr_name);
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
    Bool            Object::LT(Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Bool            Object::operator < (Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Bool            Object::LE(Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Bool            Object::operator <= (Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Bool            Object::EQ(Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Object::operator == (Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Object::NE(Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Bool            Object::operator != (Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Bool            Object::GT(Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Bool            Object::operator > (Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Bool            Object::GE(Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_GE)); }
    Bool            Object::operator >= (Object other) const { return FromNew<Bool>(PyObject_RichCompare(m_ref, other, Py_GE)); }
    /* -------------------------------------------------------------------------- */
    /*                          Common object operations                          */
    /* -------------------------------------------------------------------------- */
    Str             Object::Repr() const { return FromNew<Str>(PyObject_Repr(m_ref)); }
    Str             Object::ASCII() const { return FromNew<Str>(PyObject_ASCII(m_ref)); }
    Str             Object::ToStr() const { return FromNew<Str>(PyObject_Str(m_ref)); }
    Bytes           Object::ToBytes() const { return FromNew<Bytes>(PyObject_Bytes(m_ref)); }
    Py_hash_t       Object::Hash() const { return PyObject_Hash(m_ref); }
    bool            Object::IsTrue() const { return PyObject_IsTrue(m_ref); }
    bool            Object::Not() const { return PyObject_Not(m_ref); }
    Py_ssize_t      Object::Size() const { return PyObject_Size(m_ref); }
    Py_ssize_t      Object::Length() const { return PyObject_Length(m_ref); }

}
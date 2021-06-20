#include "Object.hh"


namespace Py
{
    Object::Object() : m_ref(nullptr) {
        __LOG("Object FromNew!");
    }
    Object::Object(PyObject* py_object)
        : m_ref(py_object) {
        __LOG("Object FromNew!");
    }
    Object::Object(const Object& moved_object)
        : m_ref(moved_object.m_ref) {
        Py_XINCREF(moved_object.m_ref);
        __LOG("Object Copied!");
    }
    Object::Object(Object&& moved_object)
        : m_ref(moved_object.m_ref) {
        moved_object.m_ref = nullptr;
        //Py_XINCREF(moved_object.m_ref);
        __LOG("Object Moved!");
    }
    /* -------------------------------------------------------------------------- */
    /*                 Implicit dynamic casts among wrapper types                 */
    /* -------------------------------------------------------------------------- */
    Object::operator Object () { return Old<Object>(m_ref); }
    Object::operator Long () { return Old<Long>(m_ref); }
    Object::operator Float () { return Old<Float>(m_ref); }
    Object::operator Complex () { return Old<Complex>(m_ref); }
    Object::operator Bool () { return Old<Bool>(m_ref); }
    Object::operator Str () { return Old<Str>(m_ref); }
    Object::operator Bytes () { return Old<Bytes>(m_ref); }
    Object::operator ByteArray () { return Old<ByteArray>(m_ref); }
    Object::operator List () { return Old<List>(m_ref); }
    Object::operator Tuple () { return Old<Tuple>(m_ref); }
    Object::operator Dict () { return Old<Dict>(m_ref); }
    Object::operator Set () { return Old<Set>(m_ref); }
    Object::operator FrozenSet () { return Old<FrozenSet>(m_ref); }
    /* -------------------------------------------------------------------------- */
    /*                          Getters, setter, deleters                         */
    /* -------------------------------------------------------------------------- */
    bool            Object::HasAttr(Str attr_name) const {
        return PyObject_HasAttr(m_ref, attr_name);
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
    Object          Object::GetItem(Object attr_name) const {
        return PyObject_GetItem(m_ref, attr_name);
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
    Bool            Object::__lt__(Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Bool            Object::operator < (Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_LT)); }
    Bool            Object::__le__(Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Bool            Object::operator <= (Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_LE)); }
    Bool            Object::__eq__(Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Object::operator == (Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Object::__ne__(Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Bool            Object::operator != (Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_NE)); }
    Bool            Object::__gt__(Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Bool            Object::operator > (Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_GT)); }
    Bool            Object::__ge__(Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_GE)); }
    Bool            Object::operator >= (Object other) const { return New<Bool>(PyObject_RichCompare(m_ref, other, Py_GE)); }
    /* -------------------------------------------------------------------------- */
    /*                          Common object operations                          */
    /* -------------------------------------------------------------------------- */
    Str             Object::Repr() const { return New<Str>(PyObject_Repr(m_ref)); }
    std::string     Object::ReprCStr() const {
        auto temp = PyObject_Repr(m_ref);
        const std::string temp_str = PyUnicode_AsUTF8(temp);
        Py_XDECREF(temp);
        return temp_str;
    }
    Str             Object::ASCII() const { return New<Str>(PyObject_ASCII(m_ref)); }
    Str             Object::ToStr() const { return New<Str>(PyObject_Str(m_ref)); }
    Bytes           Object::ToBytes() const { return New<Bytes>(PyObject_Bytes(m_ref)); }
    Py_hash_t       Object::Hash() const { return PyObject_Hash(m_ref); }
    bool            Object::IsTrue() const { return PyObject_IsTrue(m_ref); }
    bool            Object::Not() const { return PyObject_Not(m_ref); }
    Py_ssize_t      Object::Size() const { return PyObject_Size(m_ref); }
    Py_ssize_t      Object::Length() const { return PyObject_Length(m_ref); }
    // IO stream overload
    std::ostream& operator << (std::ostream& os, Object py_object) {
        return os << py_object.ReprCStr();
        //return os << "Py[" << py_object.GetRef()->ob_type->tp_name << "](" << py_object.ReprCStr() << ')';
    }

}


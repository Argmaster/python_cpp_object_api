#include "Object.hh"


namespace Py
{
    Object::Object() : m_ref(nullptr) {
        __LOG("Object New!");
    }
    Object::Object(PyObject* py_object)
        : m_ref(py_object) {
        __LOG("Object From!");
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
    int             Object::LessThan(Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_LT)); }
    int             Object::operator < (Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_LT)); }
    int             Object::LessEqual(Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_LE)); }
    int             Object::operator <= (Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_LE)); }
    int             Object::Equals(Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    int             Object::operator == (Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_EQ)); }
    int             Object::NotEquals(Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_NE)); }
    int             Object::operator != (Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_NE)); }
    int             Object::GreaterThan(Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_GT)); }
    int             Object::operator > (Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_GT)); }
    int             Object::GreaterEqual(Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_GE)); }
    int             Object::operator >= (Object other) const { return PyObject_IsTrue(PyObject_RichCompare(m_ref, other, Py_GE)); }
    /* -------------------------------------------------------------------------- */
    /*                             Numerical operators                            */
    /* -------------------------------------------------------------------------- */
    Object          Object::Add(Object other) const { return PyNumber_Add(m_ref, other); }
    Object          Object::operator + (Object other) const { return PyNumber_Add(m_ref, other); }
    Object          Object::Sub(Object other) const { return PyNumber_Subtract(m_ref, other); }
    Object          Object::operator - (Object other) const { return PyNumber_Subtract(m_ref, other); }
    Object          Object::Mul(Object other) const { return PyNumber_Multiply(m_ref, other); }
    Object          Object::operator * (Object other) const { return PyNumber_Multiply(m_ref, other); }
    Object          Object::MatMul(Object other) const { return PyNumber_MatrixMultiply(m_ref, other); }
    Object          Object::FloorDiv(Object other) const { return PyNumber_FloorDivide(m_ref, other); }
    Object          Object::TrueDiv(Object other) const { return PyNumber_TrueDivide(m_ref, other); }
    Object          Object::operator / (Object other) const { return PyNumber_TrueDivide(m_ref, other); }
    Object          Object::Mod(Object other) const { return PyNumber_Remainder(m_ref, other); }
    Object          Object::operator %(Object other) const { return PyNumber_Remainder(m_ref, other); }
    Object          Object::DivMod(Object other) const { return PyNumber_Divmod(m_ref, other); }
    Object          Object::Pow(Object other) const { return PyNumber_Power(m_ref, other, Py_None); }
    Object          Object::Neg() const { return PyNumber_Negative(m_ref); }
    Object          Object::operator - () const { return PyNumber_Negative(m_ref); }
    Object          Object::Pos() const { return PyNumber_Positive(m_ref); }
    Object          Object::operator + () const { return PyNumber_Positive(m_ref); }
    Object          Object::Abs() const { return PyNumber_Absolute(m_ref); }
    Object          Object::Inv() const { return PyNumber_Invert(m_ref); }
    Object          Object::operator ~ () const { return PyNumber_Invert(m_ref); }
    Object          Object::LShift(Object other) const { return PyNumber_Lshift(m_ref, other); }
    Object          Object::operator << (Object other) const { return PyNumber_Lshift(m_ref, other); }
    Object          Object::RShift(Object other) const { return PyNumber_Rshift(m_ref, other); }
    Object          Object::operator >> (Object other) const { return PyNumber_Rshift(m_ref, other); }
    Object          Object::And(Object other) const { return PyNumber_And(m_ref, other); }
    Object          Object::operator & (Object other) const { return PyNumber_And(m_ref, other); }
    Object          Object::Or(Object other) const { return PyNumber_Or(m_ref, other); }
    Object          Object::operator | (Object other) const { return PyNumber_Or(m_ref, other); }
    Object          Object::Xor(Object other) const { return PyNumber_Xor(m_ref, other); }
    Object          Object::operator ^ (Object other) const { return PyNumber_Xor(m_ref, other); }
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
    Object          Object::Call(Tuple args, Dict kwargs) { return New<Object>(PyObject_Call(m_ref, args, kwargs)); }
    Object          Object::Call(std::string name, Tuple args, Dict kwargs) {
        if (args.IsNull())
            return New<Object>(PyObject_Call(GetAttr(name), Tuple({}), kwargs));
        else
            return New<Object>(PyObject_Call(GetAttr(name), args, kwargs));
    }
    // IO stream overload
    std::ostream& operator << (std::ostream& os, Object py_object) {
        return os << py_object.ReprCStr();
        //return os << "Py[" << py_object.GetRef()->ob_type->tp_name << "](" << py_object.ReprCStr() << ')';
    }
}


#include "Object.hh"


namespace Py
{
    namespace Modules
    {
        Module* traceback = nullptr;
        Module* inspect = nullptr;
        Module* json = nullptr;
    };
    Object::Object(PyObject* py_object)
        : m_ref(py_object) {
    }
    Object::Object(const Object& copied_object)
        : m_ref(copied_object.m_ref) {
        Py_XINCREF(copied_object.m_ref);
    }
    Object::Object(Object&& moved_object)
        : m_ref(moved_object.m_ref) {
        moved_object.m_ref = nullptr;
    }
    /* -------------------------------------------------------------------------- */
    /*                          Getters, setter, deleters                         */
    /* -------------------------------------------------------------------------- */
    bool            Object::HasAttr(Str attr_name) const {
        return PyObject_HasAttr(m_ref, attr_name);
    }
    Object          Object::GetAttr(Str attr_name) const {
        auto attr = PyObject_GetAttr(m_ref, attr_name);
        if (attr == NULL) {
            Py::Exception::Raise(
                PyExc_AttributeError,
                Py::Str::FromFormat("Attribute '%s' doesn't exist", attr_name.AsUTF8().c_str())
            );
        }
        return attr;
    }
    void            Object::SetAttr(Str attr_name, PyObject* value) const {
        auto retval = PyObject_SetAttr(m_ref, attr_name, value);
        if (retval == -1) {
            Exception::Raise(
                PyExc_AttributeError,
                Py::Str::FromFormat("Failed to set attribute '%s'", attr_name.AsUTF8().c_str())
            );
        }
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
    Str             Object::Repr() const {
        if (IsNotNull()) {
            return New<Str>(PyObject_Repr(m_ref));
        } else
            return Str("<PyObject NULL>");
    }
    std::string     Object::ReprCStr() const {
        if (IsNotNull()) {
            auto repr = PyObject_Repr(m_ref);
            if (repr == NULL) {
                Exception::Clear();
                repr = PyObject_Str(m_ref);
            }
            return PyUnicode_AsUTF8(repr);
        } else
            return "<PyObject NULL>";
    }
    Str             Object::ASCII() const { return New<Str>(PyObject_ASCII(m_ref)); }
    Str             Object::ToStr() const { return New<Str>(PyObject_Str(m_ref)); }
    Bytes           Object::ToBytes() const { return New<Bytes>(PyObject_Bytes(m_ref)); }
    Py_hash_t       Object::Hash() const { return PyObject_Hash(m_ref); }
    bool            Object::IsTrue() const { return PyObject_IsTrue(m_ref); }
    bool            Object::Not() const { return PyObject_Not(m_ref); }
    Py_ssize_t      Object::Size() const { return PyObject_Size(m_ref); }
    Py_ssize_t      Object::Length() const { return PyObject_Length(m_ref); }
    Object          Object::Call(Tuple args, Dict kwargs) {
        return New<Object>(PyObject_Call(m_ref, args, kwargs));
    }
    Object          Object::Call(std::string name, Tuple args, Dict kwargs) {
        Object callable = GetAttr(name);
        return New<Object>(PyObject_Call(callable, args, kwargs));
    }
    // IO stream overload
    std::ostream& operator << (std::ostream& os, const Object& py_object) {
        const std::string buff = py_object.ReprCStr();
        os.write(buff.c_str(), buff.length());
        return os;
    }
}


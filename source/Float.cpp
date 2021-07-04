#include <Float.hh>


namespace Py
{
    Float::Float(long double _value)
        : Object(nullptr) {
        m_ref = PyFloat_FromDouble(_value);
    }
    Float::Float(Py::Str _value)
        : Object(nullptr) {
        m_ref = PyFloat_FromString(_value);
    }
} // namespace Py

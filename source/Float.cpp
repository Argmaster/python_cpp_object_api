#include <Float.hh>


namespace Py
{
    Float::Float(long double _value) : Object(nullptr) {
        m_ref = PyFloat_FromDouble(_value);
    }
} // namespace Py

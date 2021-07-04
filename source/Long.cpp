#include <Long.hh>


namespace Py
{
    Long::Long(int64_t _long)
        : Object(nullptr) {
        m_ref = PyLong_FromLongLong(_long);
    }
    Long::Long(Py::Str _value, int base)
        : Object(nullptr) {
        m_ref = PyLong_FromUnicodeObject(_value, base);
    }
} // namespace Py

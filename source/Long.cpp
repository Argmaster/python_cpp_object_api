#include <Long.hh>


namespace Py
{
    Long::Long(int64_t _long) : Object(nullptr) {
        m_ref = PyLong_FromLongLong(_long);
    }
    Long(std::string _value, int base = 10) {
        m_ref = PyLong_FromString(_value.begin(), _value.end(), base);
    }
    Long::Long(Py::Str _value, int base) {
        m_ref = PyLong_FromUnicodeObject(_value, base);
    }
} // namespace Py

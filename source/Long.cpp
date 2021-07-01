#include <Long.hh>


namespace Py
{
    Long::Long(long _long) : Object(nullptr) {
        m_ref = PyLong_FromLong(_long);
    }
} // namespace Py

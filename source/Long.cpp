#include <Long.hh>


namespace Py
{
    Long::Long(long _long) {
        m_ref = PyLong_FromLong(_long);
    }
} // namespace Py

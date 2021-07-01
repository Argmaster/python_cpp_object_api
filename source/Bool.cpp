#include "Bool.hh"

namespace Py
{
    Bool::Bool(bool _bool) : Object(nullptr) {
        m_ref = PyBool_FromLong(_bool);
    }
} // namespace Py

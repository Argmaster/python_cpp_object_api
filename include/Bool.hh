#pragma once
#include "Object.hh"

namespace Py
{
    class Bool : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        Bool(bool _bool) {
            m_ref = PyBool_FromLong(_bool);
        }
        friend bool operator == (bool first, Bool second) { return first == bool(second); }
        friend bool operator != (bool first, Bool second) { return first != bool(second); }
        friend bool operator == (Bool first, bool second) { return bool(first) == second; }
        friend bool operator != (Bool first, bool second) { return bool(first) != second; }
    };
}
#pragma once
#include "Object.hh"

namespace Py
{
    class Bool : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        static Bool New(bool _bool) {
            return PyBool_FromLong(_bool);
        }
        friend bool operator > (bool first, Bool second);
        friend bool operator >= (bool first, Bool second);
        friend bool operator == (bool first, Bool second);
        friend bool operator != (bool first, Bool second);
        friend bool operator < (bool first, Bool second);
        friend bool operator <= (bool first, Bool second);
        friend bool operator > (Bool first, bool second);
        friend bool operator >= (Bool first, bool second);
        friend bool operator == (Bool first, bool second);
        friend bool operator != (Bool first, bool second);
        friend bool operator < (Bool first, bool second);
        friend bool operator <= (Bool first, bool second);
    };
}
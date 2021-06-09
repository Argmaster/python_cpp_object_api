#pragma once
#include "Object.hh"

namespace Py
{
    class Long : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        static Long New(long _long) {
            return PyLong_FromLong(_long);
        }

    };
}
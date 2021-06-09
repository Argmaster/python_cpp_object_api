#pragma once
#include "Object.hh"

namespace Py
{
    class Long : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        Long(long _long) {
            m_ref = PyLong_FromLong(_long);
        }

    };
}
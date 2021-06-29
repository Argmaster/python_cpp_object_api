#pragma once
#include "Object.hh"

namespace Py
{
    class Long : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C long to Python Long
        Long(long _long);

    };
}
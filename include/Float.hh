#pragma once
#include "Object.hh"
namespace Py
{
    class Float : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C float to Python Float
        Float(long double _value);

    };
}
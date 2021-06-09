#pragma once
#include "Object.hh"
namespace Py
{
    class Float : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        static Float New(long double _value) {
            return PyFloat_FromDouble(_value);
        }

    };
}
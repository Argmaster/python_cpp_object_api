#pragma once
#include "Object.hh"

namespace Py
{
    class Complex : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C doubles to Python Complex
        Complex(long double _real, long double _imag);

    };
}
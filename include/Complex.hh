#pragma once
#include "Object.hh"

namespace Py
{
    class Complex : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        static Complex New(long double _real, long double _imag) {
            return PyComplex_FromDoubles(_real, _imag);
        }

    };
}
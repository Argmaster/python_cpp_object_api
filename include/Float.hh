#pragma once
#include "Object.hh"
namespace Py
{
    class Float : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        Float(long double _value) : Object(nullptr) {
            m_ref = PyFloat_FromDouble(_value);
        }

    };
}
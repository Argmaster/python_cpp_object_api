#pragma once
#include "Object.hh"

namespace Py
{
    class Bytes : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        static Bytes New(const std::string& _string) {
            return PyBytes_FromStringAndSize(_string.c_str(), _string.length());
        }

    };
}
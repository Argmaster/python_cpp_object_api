#pragma once
#include "Object.hh"

namespace Py
{
    class ByteArray : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        static ByteArray New(const std::string& _string) {
            return PyByteArray_FromStringAndSize(_string.c_str(), _string.length());
        }

    };
}
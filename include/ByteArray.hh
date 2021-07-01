#pragma once
#include "Object.hh"

namespace Py
{
    class ByteArray : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        ByteArray(const std::string& _string) : Object(nullptr) {
            m_ref = PyByteArray_FromStringAndSize(_string.c_str(), _string.length());
        }

    };
}
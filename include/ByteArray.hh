#pragma once
#include "Object.hh"

namespace Py
{
    class ByteArray : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C++ std::string to Python bytearray
        ByteArray(const std::string& _string);
    };
}
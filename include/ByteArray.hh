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
        // construct bytearray from data of given length
        ByteArray(const void* data, const Py_ssize_t length);
        // Return the contents of bytearray as a char array after checking for a NULL pointer.
        // The returned array always has an extra null byte appended.
        char* AsCString() const;
    };
}
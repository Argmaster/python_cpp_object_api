#pragma once
#include "Object.hh"

namespace Py
{
    class Bytes : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C bool to Python Bool
        Bytes(const std::string& _string) {
            m_ref = PyBytes_FromStringAndSize(_string.c_str(), _string.length());
        }
        /*
            Take a C printf()-style format string and a variable number of arguments,
            calculate the size of the resulting Python bytes object and return a bytes
            object with the values formatted into it. The variable arguments must be C
            types and must correspond exactly to the format characters in the format
            string. The following format characters are allowed:
        */
        static Bytes FromFormat(const std::string& _format, ...) {
            return PyBytes_FromFormatV(_format.c_str(), va_list());
        }
        operator char*() { return PyBytes_AsString(m_ref); }
        operator const char*() const { return PyBytes_AsString(m_ref); }
        /* -------------------------------------------------------------------------- */
        /*                          Python Bytes Object C API                         */
        /* -------------------------------------------------------------------------- */
        /*
            Return a pointer to the contents of o. The pointer refers to the internal
            buffer of o, which consists of len(o) + 1 bytes. The last byte in the
            buffer is always null, regardless of whether there are any other null bytes.
            The data must not be modified in any way, unless the object was just created
            using PyBytes_FromStringAndSize(NULL, size). It must not be deallocated.
            If o is not a bytes object at all, PyBytes_AsString() returns NULL and
            raises TypeError.
        */
        char*   AsString() const;
        /*
            Create a new bytes object in *bytes containing the contents of newpart
            appended to bytes; the caller will own the new reference. The reference to
            the old value of bytes will be stolen. If the new object cannot be created,
            the old reference to bytes will still be discarded and the value of *bytes
            will be set to NULL; the appropriate exception will be set.
        */
        void    Push(Bytes other);
        /*
            A way to resize a bytes object even though it is “immutable”. Only use this to
            build up a brand new bytes object; don’t use this if the bytes may already be
            known in other parts of the code. It is an error to call this function if the
            refcount on the input bytes object is not one. Pass the address of an existing
            bytes object as an lvalue (it may be written into), and the new size desired.
            On success, *bytes holds the resized bytes object and 0 is returned; the address
            in *bytes may differ from its input value. If the reallocation fails, the original
            bytes object at *bytes is deallocated, *bytes is set to NULL,
            MemoryError is set, and -1 is returned.
        */
        int     Resize(Py_ssize_t new_size);
        /*
            Create a Unicode object by contents of this Bytes object. encoding and errors have
            the same meaning as the parameters of the same name in the str() built-in function.
            The codec to be used is looked up using the Python codec registry.
            Return NULL if an exception was raised by the codec.
        */
        Str     Decode(const char *encoding = "utf-8", const char *errors = "strict");
    };
}
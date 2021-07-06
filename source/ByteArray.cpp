#include <ByteArray.hh>


namespace Py
{
    ByteArray::ByteArray(const std::string& _string)
        : Object(PyByteArray_FromStringAndSize(_string.c_str(), _string.length())) {}
    ByteArray::ByteArray(const void* data, Py_ssize_t length)
        : Object(PyByteArray_FromStringAndSize((const char*)data, length)) {}
    char* ByteArray::AsCString() const {
        return PyByteArray_AsString(m_ref);
    }
} // namespace Py

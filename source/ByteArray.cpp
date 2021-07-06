#include <ByteArray.hh>


namespace Py
{
    ByteArray::ByteArray(const std::string& _string)
        : Object(nullptr) {
        m_ref = PyByteArray_FromStringAndSize(_string.c_str(), _string.length());
    }
    char* ByteArray::AsCString() const {
        return PyByteArray_AsString(m_ref);
    }
} // namespace Py

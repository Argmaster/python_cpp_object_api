#include "Bytes.hh"


namespace Py
{
    Bytes::Bytes(const std::string& str)
        : Object(PyBytes_FromStringAndSize(str.c_str(), str.length())) {}
    Bytes::Bytes(const char* str)
        : Object(PyBytes_FromString(str)) {}
    Bytes::Bytes(const void* data, const Py_ssize_t length)
        : Object(PyBytes_FromStringAndSize((const char*)data, length)) {}
    char*       Bytes::InnerBuffer() const { return PyBytes_AsString(m_ref); }
    std::string Bytes::AsString() const { return PyBytes_AsString(m_ref); }
    void        Bytes::Push(Bytes other) { return PyBytes_Concat(&m_ref, other); }
    int         Bytes::Resize(Py_ssize_t new_size) { return _PyBytes_Resize(&m_ref, new_size); }
    Str         Bytes::Decode(const char *encoding, const char *errors) {
        return New<Str>(PyUnicode_Decode(PyBytes_AsString(m_ref), PyBytes_Size(m_ref), encoding, errors));
    }
}
#include "Bytes.hh"


namespace Py
{
    char*   Bytes::AsString() const { return PyBytes_AsString(m_ref); }
    void    Bytes::Push(Bytes other) { return PyBytes_Concat(&m_ref, other); }
    int     Bytes::Resize(Py_ssize_t new_size) { return _PyBytes_Resize(&m_ref, new_size); }
    Str     Bytes::Decode(const char *encoding, const char *errors) {
        return New<Str>(PyUnicode_Decode(PyBytes_AsString(m_ref), PyBytes_Size(m_ref), encoding, errors));
    }
}
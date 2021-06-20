#include "Str.hh"


namespace Py
{
    /* -------------------------------------------------------------------------- */
    /*                         String encoding operations                         */
    /* -------------------------------------------------------------------------- */
    std::string Str::AsUTF8() const { return PyUnicode_AsUTF8(m_ref); }
    Bytes Str::Encode(const char* encoding, const char* errors) const {
        return New<Bytes>(PyUnicode_AsEncodedString(m_ref, encoding, errors));
    }

    /* -------------------------------------------------------------------------- */
    /*                              String operations                             */
    /* -------------------------------------------------------------------------- */
    Str             Str::Concat(Str other) const { return PyUnicode_Concat(m_ref, other); }
    Str             Str::operator + (Str other) const { return PyUnicode_Concat(m_ref, other); }
    List            Str::Split(Str sep, Py_ssize_t maxsplit) const { return New<List>(PyUnicode_Split(m_ref, sep, maxsplit)); }
    List            Str::Splitlines(int keepend) const { return New<List>(PyUnicode_Splitlines(m_ref, keepend)); }
    Str             Str::Join(Object sequence) const { return PyUnicode_Join(m_ref, sequence); }
    Py_ssize_t      Str::Match(Str substr, int direction, Py_ssize_t begin, Py_ssize_t end) const {
        return PyUnicode_Tailmatch(m_ref, substr, begin, end, direction);
    }
    Py_ssize_t      Str::Find(Str substr, int direction, Py_ssize_t begin, Py_ssize_t end) const {
        return PyUnicode_Find(m_ref, substr, begin, end, direction);
    }
    Py_ssize_t      Str::Count(Str substr, Py_ssize_t begin, Py_ssize_t end) const {
        return PyUnicode_Count(m_ref, substr, begin, end);
    }
    Str             Str::Replace(Str oldstr, Str newstr, Py_ssize_t maxcount) const {
        return PyUnicode_Replace(m_ref, oldstr, newstr, maxcount);
    }
    Str             Str::CFormat(Tuple args) const {
        return PyUnicode_Format(m_ref, args);
    }
    Str             Str::operator % (Tuple args) const {
        return PyUnicode_Format(m_ref, args);
    }
    Bool            operator == (const Str& self, const char* other) { return self.AsUTF8() == other; }
}
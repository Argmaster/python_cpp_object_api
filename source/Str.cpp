#include "Str.hh"


namespace Py
{
    /* -------------------------------------------------------------------------- */
    /*                 Implicit dynamic casts among wrapper types                 */
    /* -------------------------------------------------------------------------- */
    Str::operator Object () { return Object::FromOld(m_ref); }
    Str::operator Long () { return Long::FromOld(m_ref); }
    Str::operator Float () { return Float::FromOld(m_ref); }
    Str::operator Complex () { return Complex::FromOld(m_ref); }
    Str::operator Bool () { return Bool::FromOld(m_ref); }
    //Str::operator Str () { return Str::FromOld(m_ref); }
    Str::operator Bytes () { return Bytes::FromOld(m_ref); }
    Str::operator ByteArray () { return ByteArray::FromOld(m_ref); }
    Str::operator List () { return List::FromOld(m_ref); }
    Str::operator Tuple () { return Tuple::FromOld(m_ref); }
    Str::operator Dict () { return Dict::FromOld(m_ref); }
    Str::operator Set () { return Set::FromOld(m_ref); }
    Str::operator FrozenSet () { return FrozenSet::FromOld(m_ref); }
    /* -------------------------------------------------------------------------- */
    /*                         String encoding operations                         */
    /* -------------------------------------------------------------------------- */
    bool  Str::AsUTF8() const { return PyUnicode_AsUTF8(m_ref); }
    Bytes Str::Encode(const char* encoding, const char* errors) const {
        return Bytes::FromNew(PyUnicode_AsEncodedString(m_ref, encoding, errors));
    }
    /* -------------------------------------------------------------------------- */
    /*                              String operations                             */
    /* -------------------------------------------------------------------------- */
    Str             Str::Concat(Str other) const { return Str::FromNew(PyUnicode_Concat(m_ref, other)); }
    List            Str::Split(Str sep, Py_ssize_t maxsplit) const { return List::FromNew(PyUnicode_Split(m_ref, sep, maxsplit)); }
    List            Str::Splitlines(int keepend) const { return List::FromNew(PyUnicode_Splitlines(m_ref, keepend)); }
    Str             Str::Join(Str separator, Object sequence) const { return Str::FromNew(PyUnicode_Join(separator, sequence)); }
    Py_ssize_t      Str::Tailmatch(Str substr, int direction, Py_ssize_t begin, Py_ssize_t end) const {
        return PyUnicode_Tailmatch(m_ref, substr, begin, end, direction);
    }
    Py_ssize_t      Str::Find(Str substr, int direction, Py_ssize_t begin, Py_ssize_t end) const {
        return PyUnicode_Find(m_ref, substr, begin, end, direction);
    }
    Py_ssize_t      Str::Count(Str substr, Py_ssize_t begin, Py_ssize_t end) const {
        return PyUnicode_Count(m_ref, substr, begin, end);
    }
    Str             Str::Replace(Str oldstr, Str newstr, Py_ssize_t maxcount) const {
        return Str::FromNew(PyUnicode_Replace(m_ref, oldstr, newstr, maxcount));
    }
    Str             Str::CFormat(Str format, Tuple args) const {
        return Str::FromNew(PyUnicode_Format(format, args));
    }
    /* -------------------------------------------------------------------------- */
    /*                                 Comparisons                                */
    /* -------------------------------------------------------------------------- */
    Bool            Str::LT(Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_LT)); }
    Bool            Str::operator < (Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_LT)); }
    Bool            Str::LE(Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_LE)); }
    Bool            Str::operator <= (Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_LE)); }
    Bool            Str::EQ(Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Str::operator == (Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_EQ)); }
    Bool            Str::NE(Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_NE)); }
    Bool            Str::operator != (Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_NE)); }
    Bool            Str::GT(Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_GT)); }
    Bool            Str::operator > (Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_GT)); }
    Bool            Str::GE(Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_GE)); }
    Bool            Str::operator >= (Str other) const { return Str::FromNew(PyUnicode_RichCompare(m_ref, other, Py_GE)); }
}
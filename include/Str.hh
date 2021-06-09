#pragma once
#include "Common.hh"


namespace Py
{
    struct Str : public __WrapperInterface
    {
        using __WrapperInterface::__WrapperInterface;
        Str(const char* str) : __WrapperInterface(nullptr) {
            m_ref = PyUnicode_FromString(str);
        }
        /// Construct Str out of New PyObject Reference
        static Str FromNew(PyObject* py_new_ref) { return Str(py_new_ref); } // ! new reference construction
        /// Construct Str out of Borrowed PyObject Reference
        static Str FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Str(py_weak_ref); } // ? borrowed reference construction
        static Str New(std::string _string) {
            return Str::FromNew(
                PyUnicode_FromStringAndSize(_string.c_str(), _string.length())
            );
        }
        /* -------------------------------------------------------------------------- */
        /*                 Implicit dynamic casts among wrapper types                 */
        /* -------------------------------------------------------------------------- */
        operator Object ();
        operator Long ();
        operator Float ();
        operator Complex ();
        operator Bool ();
        //operator Str ();
        operator Bytes ();
        operator ByteArray ();
        operator List ();
        operator Tuple ();
        operator Dict ();
        operator Set ();
        operator FrozenSet ();
        /* -------------------------------------------------------------------------- */
        /*                         Python Unicode Object C API                        */
        /* -------------------------------------------------------------------------- */
        /* -------------------------------------------------------------------------- */
        /*                         String encoding operations                         */
        /* -------------------------------------------------------------------------- */
        // Return a pointer to the UTF-8 encoding of the Unicode object.
        // The returned buffer always has an extra null byte appended(not included in size),
        // regardless of whether there are any other null code points.
        std::string AsUTF8() const;
        /*
            Encode a Unicode object with selected charmap and return the result as Python bytes object.
            The default for errors is 'strict', meaning that encoding errors raise a UnicodeError.
            Other possible values are 'ignore', 'replace', 'xmlcharrefreplace', 'backslashreplace'
            and any other name registered via codecs.register_error(), see section Error Handlers.
            For a list of possible encodings, see section Standard Encodings.
        */
        Bytes       Encode(const char* encoding, const char* errors = "strict") const;
        /*
            Create a Unicode object by decoding size bytes of the encoded string s. encoding and
            errors have the same meaning as the parameters of the same name in the str() built-in function.
            The codec to be used is looked up using the Python codec registry. Return NULL if an exception
            was raised by the codec.
        */
        static Str  Decode(const std::string& source, const char* encoding, const char* errors) {
            return FromNew(PyUnicode_Decode(source.c_str(), source.length(), encoding, errors));
        }
        /* -------------------------------------------------------------------------- */
        /*                              String operations                             */
        /* -------------------------------------------------------------------------- */
        // Concat two strings giving a new Unicode string.
        Str         Concat(Str other) const;
        /*
            Split a string giving a list of Unicode strings. If sep is NULL,
            splitting will be done at all whitespace substrings. Otherwise,
            splits occur at the given separator. At most maxsplit splits
            will be done. If negative, no limit is set. Separators are not
            included in the resulting list.
        */
        List        Split(Str sep, Py_ssize_t maxsplit = INT64_MAX) const;
        /*
            Split a Unicode string at line breaks, returning a list of Unicode strings.
            CRLF is considered to be one line break. If keepend is 0, the Line break
            characters are not included in the resulting strings.
        */
        List        Splitlines(int keepend = 0) const;
        Str         Join(Str separator, Object sequence) const;
        Py_ssize_t  Tailmatch(Str substr, int direction = 1, Py_ssize_t begin = 0, Py_ssize_t end = INT64_MAX) const;
        Py_ssize_t  Find(Str substr, int direction = 1, Py_ssize_t begin = 0, Py_ssize_t end = INT64_MAX) const;
        Py_ssize_t  Count(Str substr, Py_ssize_t begin = 0, Py_ssize_t end = INT64_MAX) const;
        Str         Replace(Str oldstr, Str newstr, Py_ssize_t maxcount = INT64_MAX) const;
        Str         CFormat(Str format, Tuple args) const;
        /* -------------------------------------------------------------------------- */
        /*                                 Comparisons                                */
        /* -------------------------------------------------------------------------- */
        /// Less than comparison. This is the equivalent of the Python expression a < b
        Bool            LT(Str other) const;
        /// Less than comparison. This is the equivalent of the Python expression a < b
        Bool            operator < (Str other) const;
        /// Less or equal comparison. This is the equivalent of the Python expression a <= b
        Bool            LE(Str other) const;
        /// Less or equal comparison. This is the equivalent of the Python expression a <= b
        Bool            operator <= (Str other) const;
        /// Equal comparison. This is the equivalent of the Python expression a == b
        Bool            EQ(Str other) const;
        /// Equal comparison. This is the equivalent of the Python expression a == b
        Bool            operator == (Str other) const;
        /// Not equal comparison. This is the equivalent of the Python expression a != b
        Bool            NE(Str other) const;
        /// Not equal comparison. This is the equivalent of the Python expression a != b
        Bool            operator != (Str other) const;
        /// Greater than comparison. This is the equivalent of the Python expression a > b
        Bool            GT(Str other) const;
        /// Greater than comparison. This is the equivalent of the Python expression a > b
        Bool            operator > (Str other) const;
        /// Greater or equal comparison. This is the equivalent of the Python expression a >= b
        Bool            GE(Str other) const;
        /// Greater or equal comparison. This is the equivalent of the Python expression a >= b
        Bool            operator >= (Str other) const;
    };
}
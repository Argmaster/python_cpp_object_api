#pragma once
#include "Object.hh"

namespace Py
{
    class Str : public Object
    {
    public:
        using Object::Object;
        Str(const char* str) : Object(nullptr) {
            m_ref = PyUnicode_FromString(str);
        }
        template<typename... Args>
        static Str FromFormat(const std::string& _format, Args... args) {
            return PyUnicode_FromFormat(_format.c_str(), args...);
        }
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
        Bytes       Encode(const char* encoding = "utf-8", const char* errors = "strict") const;
        /*
            Create a Unicode object by decoding size bytes of the encoded string s. encoding and
            errors have the same meaning as the parameters of the same name in the str() built-in function.
            The codec to be used is looked up using the Python codec registry. Return NULL if an exception
            was raised by the codec.
        */
        static Str  Decode(const std::string& source, const char* encoding = "utf-8", const char* errors = "strict") {
            return PyUnicode_Decode(source.c_str(), source.length(), encoding, errors);
        }
        /* -------------------------------------------------------------------------- */
        /*                              String operations                             */
        /* -------------------------------------------------------------------------- */
        // Concat two strings returning a new Unicode object.
        Str         Concat(Str other) const;
        // Concat two strings returning a new Unicode object.
        Str         operator + (Str other) const;
        /*
            Split a string giving a list of Unicode strings. If sep is NULL,
            splitting will be done at all whitespace substrings. Otherwise,
            splits occur at the given separator. At most maxsplit splits
            will be done. If negative, no limit is set. Separators are not
            included in the resulting list.
        */
        List        Split(Str sep, Py_ssize_t maxsplit = PY_SSIZE_T_MAX) const;
        /*
            Split a Unicode string at line breaks, returning a list of Unicode strings.
            CRLF is considered to be one line break. If keepend is 0, the Line break
            characters are not included in the resulting strings.
        */
        List        Splitlines(int keepend = 0) const;
        // Join a sequence of strings using the given separator and return the resulting Unicode string.
        Str         Join(Object sequence) const;
        /*
            Return 1 if substr matches str[start:end] at the given tail end
            (direction == -1 means to do a prefix match, direction == 1 a suffix match),
            0 otherwise. Return -1 if an error occurred.
        */
        Py_ssize_t  Match(Str substr, int direction = -1, Py_ssize_t begin = 0, Py_ssize_t end = PY_SSIZE_T_MAX) const;
        /*
            Return the first position of substr in str[start:end] using the given
            direction (direction == 1 means to do a forward search,
            direction == -1 a backward search). The return value is the index of
            the first match; a value of -1 indicates that no match was found, and
            -2 indicates that an error occurred and an exception has been set.
        */
        Py_ssize_t  Find(Str substr, int direction = 1, Py_ssize_t begin = 0, Py_ssize_t end = PY_SSIZE_T_MAX) const;
        // Return the number of non-overlapping occurrences of substr in str[start:end].
        // Return - 1 if an error occurred.
        Py_ssize_t  Count(Str substr, Py_ssize_t begin = 0, Py_ssize_t end = PY_SSIZE_T_MAX) const;
        /*
            Replace at most maxcount occurrences of substr in str with replstr and
            return the resulting Unicode object. maxcount == -1 means replace all occurrences.
        */
        Str         Replace(Str oldstr, Str newstr, Py_ssize_t maxcount = PY_SSIZE_T_MAX) const;
        // Return a new string object by injecting args into string; this is analogous to format % args
        Str         CFormat(Tuple args) const;
        // Return a new string object from format and args; this is analogous to Str(format).CFormat(args)
        Str         operator % (Tuple args) const;
    };
}
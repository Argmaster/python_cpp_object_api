#pragma once
#include "Object.hh"

namespace Py
{
    class Long : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C long to Python Long
        Long(int64_t _long);
        // Parse integer value out of string
        Long(Py::Str _value, int base = 10);
        /*
            Return a C long long representation of obj. If obj is not an instance of
            PyLongObject, first call its __index__() or __int__() method (if present)
            to convert it to a PyLongObject.

            Raise OverflowError if the value of obj is out of range for a long long.

            Returns -1 on error. Use PyErr_Occurred() to disambiguate.
        */
        inline int64_t AsLongLong() { return PyLong_AsLongLong(m_ref); }
        /*
            Return a C double representation of pylong. pylong must be an instance of
            PyLongObject.

            Raise OverflowError if the value of pylong is out of range for a double.

            Returns -1.0 on error. Use PyErr_Occurred() to disambiguate.
        */
        inline double AsDouble() { return PyLong_AsDouble(m_ref); }
        /*
            Return a C long long representation of obj. If obj is not an instance of
            PyLongObject, first call its __index__() or __int__() method (if present)
            to convert it to a PyLongObject.

            If the value of obj is greater than LLONG_MAX or less than LLONG_MIN,
            set *overflow to 1 or -1, respectively, and return -1; otherwise,
            set *overflow to 0. If any other exception occurs set *overflow to 0
            and return -1 as usual.

            Returns -1 on error. Use PyErr_Occurred() to disambiguate.
        */
        inline int64_t AsLongLong_Overflow(int *overflow) { return PyLong_AsLongLongAndOverflow(m_ref, overflow); }
    };
}
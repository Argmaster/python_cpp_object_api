#pragma once
#include "Object.hh"
namespace Py
{
    class Float : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C float to Python Float
        Float(long double _value);
        // Parse float value from string
        Float(Py::Str _value);
        /*
            Return a C double representation of the contents of pyfloat.
            If pyfloat is not a Python floating point object but has a __float__()
            method, this method will first be called to convert pyfloat into a
            float. If __float__() is not defined then it falls back to __index__().
            This method returns -1.0 upon failure, so one should call PyErr_Occurred()
            to check for errors.
        */
        double AsDouble() { return PyFloat_AsDouble(m_ref); }
    };
}
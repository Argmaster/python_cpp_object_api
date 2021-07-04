#pragma once
#include "Object.hh"

namespace Py
{
    class Complex : public Object
    {
    public:
        using Object::Object;
        // Custom class constuctor from C doubles to Python Complex
        Complex(long double _real, long double _imag);
        Complex(std::complex<double> _cmplx)
            : Object(nullptr) {
            m_ref = PyComplex_FromDoubles(_cmplx.real(), _cmplx.imag());
        }
        // Return the real part of op as a C double.
        inline double RealAsDouble() { return PyComplex_RealAsDouble(m_ref); }
        // Return the imaginary part of op as a C double.
        inline double ImagAsDouble() { return PyComplex_ImagAsDouble(m_ref); }
        /*
            Return the std::complex<double> value of the complex number op.

            If op is not a Python complex number object but has a __complex__() method,
            this method will first be called to convert op to a Python complex number
            object. If __complex__() is not defined then it falls back to __float__().
            If __float__() is not defined then it falls back to __index__(). Upon failure,
            this method returns -1.0 as a real value.
        */
        inline std::complex<double> AsComplex() {
            Py_complex cmplx = PyComplex_AsCComplex(m_ref);
            return { cmplx.real, cmplx.imag };
        }
    };
}
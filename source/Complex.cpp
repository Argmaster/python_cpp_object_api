#include <Complex.hh>


namespace Py
{
    Complex::Complex(long double _real, long double _imag)
        : Object(nullptr) {
        m_ref = PyComplex_FromDoubles(_real, _imag);
    }
} // namespace Py

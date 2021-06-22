#include "FrozenSet.hh"


namespace Py
{
    FrozenSet::FrozenSet(std::initializer_list<Object> _elements)
        : Object(PyFrozenSet_New(NULL)) {
        for (auto e : _elements) {
            PySet_Add(m_ref, e);
        }
    }
} // namespace Py

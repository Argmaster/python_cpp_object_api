#include "Tuple.hh"

namespace Py
{
    Tuple::Tuple(std::initializer_list<Object> _elements) {
        m_ref = PyTuple_New(_elements.size());
        Py_ssize_t i = 0;
        for (auto e : _elements) {
            PyTuple_SetItem(m_ref, i, e.INCREF());
            i++;
        }
    }
    Object Tuple::GetItem(Py_ssize_t index) const {
        return Old<Object>(PyTuple_GetItem(m_ref, index));
    }
    Tuple Tuple::GetSlice(Py_ssize_t begin, Py_ssize_t end) const {
        return PyTuple_GetSlice(m_ref, begin, end);
    }
    int Tuple::SetItem(Py_ssize_t index, Object value) const {
        return PyTuple_SetItem(m_ref, index, value++);
    }
    Py_ssize_t Tuple::Size() const {
        return PyTuple_Size(m_ref);
    }
    Py_ssize_t Tuple::Length() const {
        return PyTuple_Size(m_ref);
    }
    Object Tuple::operator [](Py_ssize_t index) const {
        return New<Object>(PyTuple_GetItem(m_ref, index));
    }
}
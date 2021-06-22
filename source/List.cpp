#include "List.hh"


namespace Py
{
    List::List(std::initializer_list<Object> _elements) : Object(PyList_New(_elements.size())) {
        Py_ssize_t i = 0;
        for (auto e : _elements) {
            PyList_SetItem(m_ref, i, e++);
            i++;
        }
    }
    Object  List::GetItem(Py_ssize_t index) const {
        return Old<Object>(PyList_GetItem(m_ref, index));
    }
    Object  List::operator [] (Py_ssize_t index) const {
        return Old<Object>(PyList_GetItem(m_ref, index));
    }
    int     List::SetItem(Py_ssize_t index, Object value) const {
        return PyList_SetItem(m_ref, index, value);
    }
    List    List::GetSlice(Py_ssize_t begin, Py_ssize_t end) const {
        return New<List>(PyList_GetSlice(m_ref, begin, end));
    }
    List    List::operator [] (std::pair<Py_ssize_t, Py_ssize_t> indes) const {
        return New<List>(PyList_GetSlice(m_ref, indes.first, indes.second));
    }
    int     List::SetSlice(Py_ssize_t begin, Py_ssize_t end, List value) const {
        return PyList_SetSlice(m_ref, begin, end, value);
    }
    int     List::Append(Object item) const {
        return PyList_Append(m_ref, item);
    }
    int     List::Insert(Py_ssize_t index, Object item) const {
        return PyList_Insert(m_ref, index, item);
    }
    int     List::Sort() const {
        return PyList_Sort(m_ref);
    }
    int     List::Reverse() const {
        return PyList_Reverse(m_ref);
    }
    Tuple   List::ToTuple() const {
        return New<Tuple>(PyList_AsTuple(m_ref));
    }
} // namespace Py

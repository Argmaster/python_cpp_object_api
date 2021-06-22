#include "Set.hh"


namespace Py
{
    Set::Set(std::initializer_list<Object> _elements)
        : Object(PySet_New(NULL)) {
        for (auto e : _elements) {
            PySet_Add(m_ref, e);
        }
    }
    int Set::Clear() const {
        return PySet_Clear(m_ref);
    }
    int Set::Contains(Object element) const {
        return PySet_Contains(m_ref, element);
    }
    int Set::Add(Object element) const {
        return PySet_Add(m_ref, element);
    }
    int Set::Remove(Object element) const {
        return PySet_Discard(m_ref, element);
    }
    Object Set::Pop() const {
        return New<Object>(PySet_Pop(m_ref));
    }

} // namespace Py

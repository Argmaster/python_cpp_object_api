#pragma once
#include "Object.hh"

namespace Py
{
    class Tuple : public Object
    {
    public:
        using Object::Object;
        Tuple(std::initializer_list<Object> _elements) {
            m_ref = PyTuple_New(_elements.size());
            Py_ssize_t i = 0;
            for (auto e : _elements) {
                PyTuple_SetItem(m_ref, i, e.INCREF());
                i++;
            }
        }
    };
}
#pragma once
#include "Object.hh"
namespace Py
{
    class FrozenSet : public Object
    {
    public:
        using Object::Object;
        // Create new frozenset containing unque elements of _elements list
        FrozenSet(std::initializer_list<Object> _elements);

    };
}
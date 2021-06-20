#pragma once
#include "Object.hh"

namespace Py
{
    class Tuple : public Object
    {
    public:
        using Object::Object;
        // Construct tuple from variable count of PyObjects
        Tuple(std::initializer_list<Object> _elements);



    };
}
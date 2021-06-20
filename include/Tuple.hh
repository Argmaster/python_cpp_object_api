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
        // Return the object at position pos in the tuple. If pos is out of bounds,
        // return NULL and set an IndexError exception.
        Object GetItem(Py_ssize_t index) const;
        // Return the slice of the tuple pointed to by p between low and high, or
        // NULL on failure.This is the equivalent of the Python expression p[low:high].
        // Indexing from the end of the list is not supported
        Tuple GetSlice(Py_ssize_t begin, Py_ssize_t end) const;
        // Insert a reference to object o at position pos of the tuple Return 0 on success.
        // If pos is out of bounds, return -1 and set an IndexError exception. This method
        // doesn't steal reference to Object.
        int SetItem(Py_ssize_t index, Object value) const;
        // Return size of this tuple
        Py_ssize_t Size() const override;
        // Return size of this tuple
        Py_ssize_t Length() const override;
        // Return the object at position pos in the tuple. If pos is out of bounds,
        // return NULL and set an IndexError exception.
        Object operator [](Py_ssize_t index) const;

    };
}
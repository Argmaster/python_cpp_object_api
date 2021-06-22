#pragma once
#include "Object.hh"

namespace Py
{
    class Set : public Object
    {
    public:
        using Object::Object;
        // Create new set containing unque elements of _elements list
        Set(std::initializer_list<Object> _elements);
        /// Empty an existing set of all elements.
        int     Clear() const;
        /*
            Return 1 if found, 0 if not found, and -1 if an error is encountered.
            Unlike the Python __contains__() method, this function does not automatically
            convert unhashable sets into temporary frozensets. Raise a TypeError
            if the key is unhashable. Raise PyExc_SystemError if anyset is not a
            set, frozenset, or an instance of a subtype
        */
        int     Contains(Object element) const;
        /*
            Add key to a set instance. Also works with frozenset instances
            (like PyTuple_SetItem() it can be used to fill-in the values of
            brand new frozensets before they are exposed to other code).
            Return 0 on success or -1 on failure. Raise a TypeError if the
            key is unhashable. Raise a MemoryError if there is no room to grow.
            Raise a SystemError if set is not an instance of set or its subtype.
        */
        int     Add(Object element) const;
        /*
            Return 1 if found and removed, 0 if not found (no action taken), and -1
            if an error is encountered. Does not raise KeyError for missing keys.
            Raise a TypeError if the key is unhashable. Unlike the Python discard()
            method, this function does not automatically convert unhashable sets into
            temporary frozensets. Raise PyExc_SystemError if set is not an instance
            of set or its subtype.
        */
        int     Remove(Object element) const;
        /*
            Return a new reference to an arbitrary object in the set, and removes the
            object from the set. Return NULL on failure. Raise KeyError if the set is
            empty. Raise a SystemError if set is not an instance of set or its subtype.
        */
        Object  Pop() const;
    };
}
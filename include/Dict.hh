#pragma once
#include "Object.hh"

namespace Py
{
    class Dict : public Object
    {
    public:
        using Object::Object;
        // construct new dictionary from key value pairs
        Dict(std::initializer_list<std::pair<Str, Object>> _dict);
        // Return a new dictionary that contains the same key-value pairs as p.
        Dict    Copy() const;
        /**
            @brief Iterate over mapping object other adding key-value pairs to this dictionary.
            other may be a dictionary, or any object supporting PyMapping_Keys() and PyObject_GetItem().
            If override is true, existing pairs in a will be replaced if a matching key is found in b,
            otherwise pairs will only be added if there is not a matching key in a.
            Return 0 on success or -1 if an exception was raised.
        */
        int     Merge(Dict other, int _override = 1);
        /**
            @brief This is the same as _Merge(b, 1) in C, and is similar to a.update(b) in Python except that
            Update() doesn’t fall back to the iterating over a sequence of key value pairs if the second
            argument has no “keys” attribute. Return 0 on success or -1 if an exception was raised.
        */
        int     Update(Dict other);
        /**
            @brief Determine if dictionary p contains key. If an item in p is matches key,
            return 1, otherwise return 0. On error, return -1. This is equivalent to
            the Python expression key in p.
        */
        int     Contains(Object key);
        /**
            @brief Empty an existing dictionary of all key-value pairs.
        */
        void    Clear();
        /**
            Return the object from dictionary p which has a key key. Return NULL if the
            key key is not present, but without setting an exception.

            Note that exceptions which occur while calling __hash__() and __eq__()
            methods will get suppressed. To get error reporting use
            GetItemWithError() instead.
        */
        Object  GetItem(Str key) const;
        /*
            Variant of PyDict_GetItem() that does not suppress exceptions. Return NULL
            with an exception set if an exception occurred. Return NULL without an
            exception set if the key wasn’t present.
        */
        Object  GetItemWithError(Str key) const;
        /*
            Insert val into the dictionary p with a key of key. key must be hashable;
            if it isn’t, TypeError will be raised. Return 0 on success or -1 on failure.
            This function does not steal a reference to val.
        */
        int     SetItem(Str key, Object new_value) const;
        /*
            Remove the entry in dictionary p with key key. key must be hashable;
            if it isn’t, TypeError is raised. If key is not in the dictionary,
            KeyError is raised. Return 0 on success or -1 on failure.
        */
        int     DelItem(Str key) const;
        /*
            Return a List containing all the items from the dictionary.
        */
        List    Items() const;
        /*
            Return a List containing all the keys from the dictionary.
        */
        List    Keys() const;
        /*
            Return a List containing all the keys from the dictionary.
        */
        List    Values() const;
    };
}
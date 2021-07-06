#pragma once
#include "Object.hh"

namespace Py
{
    class Mapping : public Object
    {
    public:
        using Object::Object;
        // construct new mapping from key value pairs
        Mapping(std::initializer_list<std::pair<std::string, Object>> _dict);
        /*
            Return element of o corresponding to the string key or NULL on failure.
            This is the equivalent of the Python expression o[key]. See also PyObject_GetItem().
        */
        Object  GetItem(const std::string& key) const;
        /*
            Map the string key to the value v in object o. Returns -1 on failure.
            This is the equivalent of the Python statement o[key] = v. See also PyObject_SetItem().
            This function does not steal a reference to v.
        */
        int     SetItem(const std::string& key, Object value) const;
        /*
            Remove the mapping for the object key from the object o.
            Return -1 on failure. This is equivalent to the Python
            statement del o[key]. This is an alias of PyObject_DelItem().
        */
        int     DelItem(const std::string& key) const;
        /*
            Return 1 if the mapping object has the key key and 0 otherwise.
            This is equivalent to the Python expression key in o.
            This function always succeeds.
            Note that exceptions which occur while calling the __getitem__()
            method will get suppressed. To get error reporting use
            PyObject_GetItem() instead.
        */
        int     HasKey(const std::string& key) const;
        /*
            Return a List containing all the items from the mapping.
        */
        List    Items() const;
        /*
            Return a List containing all the keys from the mapping.
        */
        List    Keys() const;
        /*
            Return a List containing all the keys from the mapping.
        */
        List    Values() const;
    };
} // namespace Py

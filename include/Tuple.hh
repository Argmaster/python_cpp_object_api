#pragma once
#include "Object.hh"

namespace Py
{
    class Tuple : public Object
    {
    private:
        class iterator
        {
            Tuple* m_data;
            Py_ssize_t m_index;
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = Object;
            using difference_type = std::ptrdiff_t;
            using pointer = Object*;
            using reference = Object&;
        public:
            iterator(Tuple* data, Py_ssize_t index) : m_data(data), m_index(index) {}
            iterator(const iterator& iter) = default;
            ~iterator() {}
            operator bool() { return m_data->IsNotNull(); }

            bool                operator==(const iterator& other)const { return ((m_index == other.m_index) && (m_data == other.m_data)); }
            bool                operator!=(const iterator& other)const { return ((m_index != other.m_index) || (m_data != other.m_data)); }

            iterator&           operator++() { ++m_index; return (*this); }
            iterator&           operator--() { --m_index; return (*this); }

            Object              operator*() { return m_data->GetItem(m_index); }
            const Object        operator*() const { return m_data->GetItem(m_index); }
        };
    public:
        using Object::Object;
        /**
            @brief Construct tuple from variable count of PyObjects
        */
        Tuple(std::initializer_list<Object> _elements);
        /*
            construct empty tuple of size
        */
        Tuple(Py_ssize_t size);
        /*
            Parse the parameters of a function that takes only positional parameters into local
            variables. Returns true on success; on failure, it returns false and
            raises the appropriate exception.
        */
        template<typename ...Args>
        int ParseTuple(const char* format, Args... args) {
            return PyArg_ParseTuple(m_ref, format, args...);
        }
        /*
            Build Tuple or single object based on format from args.
            It builds a tuple only if its format string contains two or more format units. If
            the format string is empty, it returns None; if it contains exactly one format
            unit, it returns whatever object is described by that format unit. To force it
            to return a tuple of size 0 or one, parenthesize the format string.
            Returns the value or NULL in the case of an error; an exception will be raised if
            NULL is returned. When memory buffers are passed as parameters to supply
            data to build objects, as for the s and s# formats, the required data is
            copied. For format specifiers look at: https://docs.python.org/3/c-api/arg.html#c.Py_BuildValue
        */
        template<typename ...Args>
        static Object BuildValue(const char* format, Args... args) {
            return New<Object>(Py_BuildValue(format, args...));
        }
        /**
            @brief Return the object at position pos in the tuple. If pos is out of bounds,
                return NULL and set an IndexError exception.
        */
        Object      GetItem(Py_ssize_t index) const;
        /**
            @brief Return the slice of the tuple pointed to by p between low and high, or
                NULL on failure.This is the equivalent of the Python expression p[low:high].
                Indexing from the end of the list is not supported
        */
        Tuple       GetSlice(Py_ssize_t begin, Py_ssize_t end) const;
        /**
            @brief Insert a reference to object o at position pos of the tuple Return 0 on success.
                If pos is out of bounds, return -1 and set an IndexError exception. This method
                doesn't steal reference to Object.
        */
        int         SetItem(Py_ssize_t index, Object value) const;
        /**
            @brief Return size of this tuple
        */
        Py_ssize_t Size() const override;
        /**
            @brief Return size of this tuple
        */
        Py_ssize_t  Length() const override;
        /*
            Return the concatenation of o1 and o2 on success, and NULL on failure.
            This is the equivalent of the Python expression o1 + o2.
        */
        Object      Concat(Object other) const;
        /*
            Determine if this contains value. If an item in o is equal to value, return 1,
            otherwise return 0. On error, return -1. This is equivalent to the Python
            expression value in o.
        */
        int         Contains(Object other) const;
        /*
            Return the number of occurrences of value in this, that is, return the number of
            keys for which o[key] == value. On failure, return -1. This is equivalent to
            the Python expression o.count(value).
        */
        Py_ssize_t  Count(Object other) const;
        /*
            Return the first index i for which o[i] == value. On error, return -1. This is
            equivalent to the Python expression o.index(value).
        */
        Py_ssize_t  Index(Object other) const;
        /**
            @brief Return the object at position pos in the tuple. If pos is out of bounds,
            return NULL and set an IndexError exception.
        */
        Object      operator [](Py_ssize_t index) const;
        // Iterator begin
        iterator    begin() { return iterator(this, 0); }
        // Iterator end
        iterator    end() { return iterator(this, Length()); }
    };
}
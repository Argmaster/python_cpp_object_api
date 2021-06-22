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
        /**
            @brief Return the object at position pos in the tuple. If pos is out of bounds,
                return NULL and set an IndexError exception.
        */
        Object GetItem(Py_ssize_t index) const;
        /**
            @brief Return the slice of the tuple pointed to by p between low and high, or
                NULL on failure.This is the equivalent of the Python expression p[low:high].
                Indexing from the end of the list is not supported
        */
        Tuple GetSlice(Py_ssize_t begin, Py_ssize_t end) const;
        /**
            @brief Insert a reference to object o at position pos of the tuple Return 0 on success.
                If pos is out of bounds, return -1 and set an IndexError exception. This method
                doesn't steal reference to Object.
        */
        int SetItem(Py_ssize_t index, Object value) const;
        /**
            @brief Return size of this tuple
        */
        Py_ssize_t Size() const override;
        /**
            @brief Return size of this tuple
        */
        Py_ssize_t Length() const override;
        /**
            @brief Return the object at position pos in the tuple. If pos is out of bounds,
            return NULL and set an IndexError exception.
        */
        Object operator [](Py_ssize_t index) const;
        // Iterator begin
        iterator begin() { return iterator(this, 0); }
        // Iterator end
        iterator end() { return iterator(this, Length()); }
    };
}
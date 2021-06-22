#pragma once
#include "Object.hh"

namespace Py
{
    class List : public Object
    {
    private:
        class iterator
        {
            List* m_data;
            Py_ssize_t m_index;
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = Object;
            using difference_type = std::ptrdiff_t;
            using pointer = Object*;
            using reference = Object&;
        public:
            iterator(List* data, Py_ssize_t index) : m_data(data), m_index(index) {}
            iterator(const iterator& iter) = default;
            ~iterator() {}
            operator bool() { return m_data->IsNotNull(); }

            bool                operator==(const iterator& other)const { return ((m_index == other.m_index) && (m_data == other.m_data)); }
            bool                operator!=(const iterator& other)const { return ((m_index != other.m_index) || (m_data != other.m_data)); }

            iterator&           operator++() { ++m_index; return (*this); }
            iterator&           operator--() { --m_index; return (*this); }

            value_type          operator*() { return m_data->GetItem(m_index); }
            const value_type    operator*() const { return m_data->GetItem(m_index); }
        };
    public:
        using Object::Object;
        /**
            @brief Construct new Python List containing _elements
        */
        List(std::initializer_list<Object> _elements);
        /**
            @brief Return the object at position index in the list pointed to by list.
                The position must be non-negative; indexing from the end of the list
                is not supported. If index is out of bounds (<0 or >=len(list)),
                return NULL and set an IndexError exception
        */
        Object  GetItem(Py_ssize_t index) const;
        // Shortcut for GetItem method, has identical behaviour
        Object  operator [] (Py_ssize_t index) const;
        /**
            @brief Set the item at index index in list to item. Return 0 on success.
            If index is out of bounds, return -1 and set an IndexError exception.
            This method, in spite of its in contrast to its Python C api relative,
            PyList_SetItem, doesn't stole reference to object, however its usually
            not important, as reference counts are managed automatically
        */
        int     SetItem(Py_ssize_t index, Object value) const;
        /**
            @brief Return a list of the objects in list containing the objects between
                low and high. Return NULL and set an exception if unsuccessful. Analogous
                to list[low:high]. Indexing from the end of the list is not supported.
        */
        List    GetSlice(Py_ssize_t begin, Py_ssize_t end) const;
        // Shortcut for GetSlice method, has identical behaviour
        List    operator [] (std::pair<Py_ssize_t, Py_ssize_t> indes) const;
        /**
            @brief Set the slice of list between low and high to the contents of itemlist.
            Analogous to list[low:high] = itemlist. The itemlist may be NULL, indicating
            the assignment of an empty list (slice deletion). Return 0 on success, -1 on
            failure. Indexing from the end of the list is not supported.
        */
        int     SetSlice(Py_ssize_t begin, Py_ssize_t end, List value) const;
        /**
            @brief Append the object item at the end of list. Return 0 if successful;
                return -1 and set an exception if unsuccessful. Analogous to list.append(item).
        */
        int     Append(Object item) const;
        /**
            @brief Insert the item item into list in front of index index. Return 0 if
                successful; return -1 and set an exception if unsuccessful. Analogous to
                list.insert(index, item).
        */
        int     Insert(Py_ssize_t index, Object item) const;
        /**
            @brief Sort the items of list in place. Return 0 on success, -1 on failure.
                This is equivalent to list.sort().
        */
        int     Sort() const;
        /**
            @brief Reverse the items of list in place. Return 0 on success, -1 on failure.
                This is the equivalent of list.reverse().
        */
        int     Reverse() const;
        /**
            @brief Return a new tuple object containing the contents of list; equivalent to tuple(list).
        */
        Tuple   ToTuple() const;
        // Iterator begin
        iterator begin() { return iterator(this, 0); }
        // Iterator end
        iterator end() { return iterator(this, Length()); }
    };
}
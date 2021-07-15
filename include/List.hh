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

            Object              operator*() { return m_data->GetItem(m_index); }
            const Object        operator*() const { return m_data->GetItem(m_index); }
        };
    public:
        using Object::Object;
        /**
            @brief Construct new Python List containing _elements
        */
        List(std::initializer_list<Object> _elements);
        /**
            @brief Construct new list of size
        */
        explicit List(Py_ssize_t size);
        /**
            @brief Return the object at position index in the list pointed to by list.
                The position must be non-negative; indexing from the end of the list
                is not supported. If index is out of bounds (<0 or >=len(list)),
                Py::Exception::Error object is raised on C++ side and IndexError is set
                on Python side.
        */
        Object  GetItem(Py_ssize_t index) const;
        // Shortcut for GetItem method, has identical behaviour
        Object  operator [] (Py_ssize_t index) const;
        /**
            @brief Set the item at index index in list to item. Return 0 on success.
            If index is out of bounds, Py::Exception::Error object is raised on C++ side
            and IndexError exception is set on Python side.
            This method, in spite of its in contrast to its Python C api relative,
            PyList_SetItem, doesn't stole reference to object, however its usually
            not important, as reference counts are managed automatically
        */
        int     SetItem(Py_ssize_t index, Object value) const;
        /**
            @brief Return a list of the objects in list containing the objects between
                low and high. Analogous to list[low:high].
                Indexing from the end of the list is not supported.
                On error Py::Exception::Error object is raised on C++ side
                and Exception is set on Python side.
        */
        List    GetSlice(Py_ssize_t begin, Py_ssize_t end) const;
        // Shortcut for GetSlice method, has identical behaviour
        List    operator [] (std::pair<Py_ssize_t, Py_ssize_t> indexes) const;
        /**
            @brief Set the slice of list between low and high to the contents of itemlist.
            Analogous to list[low:high] = itemlist. The itemlist may be NULL, indicating
            the assignment of an empty list (slice deletion). Return 0 on success.
            On error Py::Exception::Error object is raised on C++ side
            and Exception is set on Python side.
            Indexing from the end of the list is not supported.
        */
        int     SetSlice(Py_ssize_t begin, Py_ssize_t end, List value) const;
        /**
            @brief Append the object item at the end of list. Return 0 if successful.
                On error Py::Exception::Error object is raised on C++ side
                and Exception is set on Python side.
                Analogous to list.append(item).
        */
        int     Append(Object item) const;
        /**
            @brief Insert the item item into list in front of index index. Return 0 if
                successful.
                On error Py::Exception::Error object is raised on C++ side
                and Exception is set on Python side.
                Analogous to list.insert(index, item).
        */
        int     Insert(Py_ssize_t index, Object item) const;
        /**
            @brief Sort the items of list in place. Return itself on success.
                On error Py::Exception::Error object is raised on C++ side
                and Exception is set on Python side.
                This is equivalent to list.sort().
        */
        List    Sort() const;
        /**
            @brief Reverse the items of list in place. Return itself on success.
                On error Py::Exception::Error object is raised on C++ side
                and Exception is set on Python side.
                This is the equivalent of list.reverse().
        */
        List    Reverse() const;
        /**
            @brief Return a new tuple object containing the contents of list; equivalent to tuple(list).
        */
        Tuple   ToTuple() const;
        /*
            Determine if this contains value. If an item in o is equal to value, return 1,
            otherwise return 0.
            On error Py::Exception::Error object is raised on C++ side
            and Exception is set on Python side.
            This is equivalent to the Python expression value in o.
        */
        int     Contains(Object other) const;
        /*
            Return the number of occurrences of value in this, that is, return the number of
            keys for which o[key] == value.
            On error Py::Exception::Error object is raised on C++ side
            and Exception is set on Python side. T
            his is equivalent to the Python expression o.count(value).
        */
        Py_ssize_t  Count(Object other) const;
        /*
            Return the first index i for which o[i] == value.
            On error Py::Exception::Error object is raised on C++ side
            and Exception is set on Python side.
            This is equivalent to the Python expression o.index(value).
        */
        Py_ssize_t  Index(Object other) const;
        // Iterator begin
        iterator    begin() { return iterator(this, 0); }
        // Iterator end
        iterator    end() { return iterator(this, Length()); }
    };
}
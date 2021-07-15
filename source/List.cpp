#include "List.hh"


namespace Py
{
    List::List( std::initializer_list<Object> _elements )
        : Object( PyList_New( _elements.size() ) )
    {
        Py_ssize_t i = 0;
        for (auto e : _elements) {
            auto retval = PyList_SetItem( m_ref, i, e++ );
            if (retval == -1)
                Py::Exception::Catch().Raise();
            i++;
        }
    }
    List::List( Py_ssize_t size )
        : Object( PyList_New( size ) )
    {}
    Object      List::GetItem( Py_ssize_t index ) const
    {
        auto retval = Old<Object>( PyList_GetItem( m_ref, index ) );
        if (retval.IsNull())
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    Object      List::operator [] ( Py_ssize_t index ) const
    {
        auto retval = Old<Object>( PyList_GetItem( m_ref, index ) );
        if (retval.IsNull())
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    int         List::SetItem( Py_ssize_t index, Object value ) const
    {
        auto retval = PyList_SetItem( m_ref, index, value++ );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    List        List::GetSlice( Py_ssize_t begin, Py_ssize_t end ) const
    {
        auto retval = New<List>( PyList_GetSlice( m_ref, begin, end ) );
        if (retval.IsNull())
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    List        List::operator [] ( std::pair<Py_ssize_t, Py_ssize_t> indes ) const
    {
        auto retval = New<List>( PyList_GetSlice( m_ref, indes.first, indes.second ) );
        if (retval.IsNull())
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    int         List::SetSlice( Py_ssize_t begin, Py_ssize_t end, List value ) const
    {
        auto retval = PyList_SetSlice( m_ref, begin, end, value );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    int         List::Append( Object item ) const
    {
        auto retval = PyList_Append( m_ref, item );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    int         List::Insert( Py_ssize_t index, Object item ) const
    {
        auto retval = PyList_Insert( m_ref, index, item );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    List        List::Sort() const
    {
        auto retval = PyList_Sort( m_ref );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return (*this);
    }
    List        List::Reverse() const
    {
        auto retval = PyList_Reverse( m_ref );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return (*this);
    }
    Tuple       List::ToTuple() const
    {
        return New<Tuple>( PyList_AsTuple( m_ref ) );
    }
    int         List::Contains( Object other ) const
    {
        auto retval = PySequence_Contains( m_ref, other );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    Py_ssize_t  List::Count( Object other ) const
    {
        auto retval = PySequence_Count( m_ref, other );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
    Py_ssize_t  List::Index( Object other ) const
    {
        auto retval = PySequence_Index( m_ref, other );
        if (retval == -1)
            Py::Exception::Catch().Raise();
        else
            return retval;
    }
} // namespace Py

#include "Dict.hh"


namespace Py
{
    Dict::Dict(std::initializer_list<std::pair<Str, Object>> _dict) : Object(PyDict_New()) {
        for (auto pair : _dict) {
            PyDict_SetItem(m_ref, pair.first, pair.second);
        }
    }
    Dict    Dict::Copy() const { return PyDict_Copy(m_ref); }
    int     Dict::Merge(Dict other, int _override) { return PyDict_Merge(m_ref, other, _override); }
    int     Dict::Update(Dict other) { return PyDict_Update(m_ref, other); }
    int     Dict::Contains(Object key) { return PyDict_Contains(m_ref, key); }
    void    Dict::Clear() { return PyDict_Clear(m_ref); }
    Object  Dict::GetItem(Str key) const { return Old<Object>(PyDict_GetItem(m_ref, key)); }
    Object  Dict::GetItemWithError(Str key) const { return Old<Object>(PyDict_GetItemWithError(m_ref, key)); }
    int     Dict::SetItem(Str key, Object new_value) const { return PyDict_SetItem(m_ref, key, new_value); }
    int     Dict::DelItem(Str key) const { return PyDict_DelItem(m_ref, key); }
    List    Dict::Items() const { return New<List>(PyDict_Items(m_ref)); }
    List    Dict::Keys() const { return New<List>(PyDict_Keys(m_ref)); }
    List    Dict::Values() const { return New<List>(PyDict_Values(m_ref)); }
}
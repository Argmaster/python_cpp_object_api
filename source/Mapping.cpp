#include "Mapping.hh"


namespace Py
{
    Mapping::Mapping(std::initializer_list<std::pair<std::string, Object>> _dict)
    : Object(PyDict_New()){
        for (auto pair : _dict) {
            PyMapping_SetItemString(m_ref, pair.first.c_str(), pair.second);
        }
    }
    Object  Mapping::GetItem(const std::string& key) const {
        return New<Object>(PyMapping_GetItemString(m_ref, key.c_str()));
    }
    int     Mapping::SetItem(const std::string& key, Object value) const {
        return PyMapping_SetItemString(m_ref, key.c_str(), value);
    }
    int     Mapping::DelItem(const std::string& key) const {
        return PyMapping_DelItemString(m_ref, key.c_str());
    }
    int     Mapping::HasKey(const std::string& key) const {
        return PyMapping_HasKeyString(m_ref, key.c_str());
    }
    List    Mapping::Items() const {
        return New<List>(PyMapping_Items(m_ref));
    }
    List    Mapping::Keys() const {
        return New<List>(PyMapping_Keys(m_ref));
    }
    List    Mapping::Values() const {
        return New<List>(PyMapping_Values(m_ref));
    }
} // namespace Py

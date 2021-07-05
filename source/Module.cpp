#include "Module.hh"


namespace Py
{
    Dict Module::GetDict() const {
        return Old<Dict>(PyModule_GetDict(m_ref));
    }
    List Module::Symbols() const {
        return New<List>(PyDict_Keys(PyModule_GetDict(m_ref)));
    }
    Str Module::GetName() const {
        return New<Str>(PyModule_GetNameObject(m_ref));
    }
    int Module::Reload() {
        Module temp_module(PyImport_ReloadModule(m_ref));
        if (temp_module.IsNull()) {
            return -1;
        } else {
            m_ref = temp_module.m_ref;
            temp_module.m_ref = nullptr;
            return 0;
        }
    }
    Module Module::Import(std::string name) {
        return PyImport_Import(Str(name));
    }
    Dict Module::GetSysModules() { return Old<Dict>(PyImport_GetModuleDict()); }
} // namespace Py
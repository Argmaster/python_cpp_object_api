#pragma once
#include "Object.hh"


namespace Py
{
    void Initialize() noexcept(false) {
        PyStatus status;
        // Initialize python interpreter in isolated mode
        PyConfig config;
        PyConfig_InitIsolatedConfig(&config);
        status = Py_InitializeFromConfig(&config);
        // clear config
        PyConfig_Clear(&config);
        // throw if initialization failed
        if (PyStatus_Exception(status)) {
            throw status;
        }
        Modules::traceback = new Module(Module::Import("traceback"));
        Modules::inspect = new Module(Module::Import("inspect"));
        Modules::json = new Module(Module::Import("json"));
        Modules::builtins = new Module(Module::Import("builtins"));
    }
    void Finalize() {
        delete Modules::traceback;
        delete Modules::inspect;
        delete Modules::json;
        delete Modules::builtins;
        if (Py_FinalizeEx() != 0) {
            throw - 1;
        }
    }
} // namespace Py

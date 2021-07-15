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
        Modules::traceback = new Module( Module::Import( "traceback" ) );
        Modules::inspect = new Module(Module::Import("inspect"));
        Modules::json = new Module(Module::Import("json"));
        Modules::builtins = new Module(Module::Import("builtins"));
    }
    /*
        Undo all initializations made by Initialize() and subsequent use of
        Python/C API functions, and destroy all sub-interpreters that were created
        and not yet destroyed since the last call to Initialize(). Ideally,
        this frees all memory allocated by the Python interpreter.
        This is a no-op when called for a second time (without calling Initialize()
        again first). If there were errors during finalization (flushing buffered data),
        Py::Exception::Error is thrown.
    */
    void Finalize()
    {
        delete Modules::traceback;
        delete Modules::inspect;
        delete Modules::json;
        delete Modules::builtins;
        if (Py_FinalizeEx() != 0) {
            throw Py::Exception::Error("Python finalization failed with exitcode -1");
        }
    }
} // namespace Py

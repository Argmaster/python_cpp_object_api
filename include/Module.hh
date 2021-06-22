#pragma once
#include "Object.hh"


namespace Py
{
    class Module : public Object
    {
    public:
        using Object::Object;
        /*
            This is a higher-level interface that calls the current “import hook function”
            (with an explicit level of 0, meaning absolute import). It invokes the
            __import__() function from the __builtins__ of the current globals. This
            means that the import is done using whatever import hooks are installed
            in the current environment. If module has already been imported, it will be
            reused and not imported again. If import fails, Module will be null and
            exception will be set.
        */
        static Module Import(std::string name);
        /*
            Return the dictionary used for the module administration (a.k.a. sys.modules).
            Note that this is a per-interpreter variable.
        */
        static Dict GetSysModules();
        /*
            Return the dictionary object that implements module’s namespace;
            this object is the same as the __dict__ attribute of the module object.
            If module is not a module object (or a subtype of a module object),
            SystemError is raised and NULL is returned.
        */
        Dict    GetDict() const;
        /*
            Get list of __dict__ keys
        */
        List    Symbols() const;
        /*
            Return module’s __name__ value. If the module does not provide one, or
            if it is not a string, SystemError is raised and NULL is returned.
        */
        Str     GetName() const;
        /*
            Reload this module. Return -1 on failure, 0 if succeded.
        */
        int     Reload();
    };
} // namespace Py

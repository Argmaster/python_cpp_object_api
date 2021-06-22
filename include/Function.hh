#pragma once
#include "Object.hh"


namespace Py
{
    class Function : public Object
    {
    public:
        using Object::Object;
        Function(std::function<PyObject*(PyObject*, PyObject*, PyObject*)> c_function, std::string function_name, std::string function_doc);
        Object operator () (Tuple args, Dict kwargs) const;
    };
} // namespace Py

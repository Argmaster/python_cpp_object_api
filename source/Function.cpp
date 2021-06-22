#include "Function.hh"


namespace Py
{
    Function::Function(std::function<PyObject*(PyObject*, PyObject*, PyObject*)> c_function, std::string function_name, std::string function_doc) {
        PyMethodDef mdef{
            function_name.c_str(),
            *(PyCFunction*)&c_function,
            METH_VARARGS | METH_KEYWORDS,
            function_doc.c_str()
        };
        m_ref = PyCFunction_NewEx(&mdef, NULL, Str(function_name));
    }
    Object Function::operator() (Tuple args, Dict kwargs) const {
        return New<Object>(PyCFunction_Call(m_ref, args, kwargs));
    }
} // namespace Py
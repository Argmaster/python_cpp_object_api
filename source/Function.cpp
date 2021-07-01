#include "Function.hh"


namespace Py
{
    namespace _CFunctionWrapperType
    {
        void        tp_dealloc(CFunctionWrapper* self) {
            if (self->c_function != nullptr) {
                delete self->c_function;
                self->c_function = nullptr;
            }
            if (self->c_signature != nullptr) {
                delete self->c_signature;
                self->c_signature = nullptr;
            }
            if (self->c_doc != nullptr) {
                delete self->c_doc;
                self->c_doc = nullptr;
            }
            Py_TYPE(self)->tp_free((PyObject*)self);
        }
        int         tp_init(CFunctionWrapper* self, PyObject* args, PyObject* kwargs) {
            return 0;
        }
        PyObject*   tp_call(PyObject* self, PyObject* args, PyObject* kwargs) {
            return Old<Object>((*((CFunctionWrapper*)self)->c_function)(
                Old<Object>(self),
                Old<Tuple>(args),
                Old<Dict>(kwargs)
                )).INCREF();
        }
        PyObject*   tp_str(CFunctionWrapper* self) {
            if (self->c_doc->length())
                return Py::Str(*self->c_signature + "\n" + *self->c_doc);
            else
                return Py::Str(*self->c_signature);
        }
        /*void        tp_finalize(CFunctionWrapper *self) {
            print("Not called");
        }*/
    }
    void init_CFunctionType() {
        if (!_CFunctionWrapperType::is_ready) {
            PyType_Ready(&CFunctionWrapperType);
            _CFunctionWrapperType::is_ready = true;
        }
    }
    Function::Function(
        PyCFunctionT c_function,
        std::string signature,
        std::string function_doc
    ) : Object(nullptr) {
        init_CFunctionType();
        m_ref = PyObject_Init(PyObject_New(PyObject, &CFunctionWrapperType), &CFunctionWrapperType);
        ((CFunctionWrapper*)m_ref)->c_function = new PyCFunctionT(c_function);
        ((CFunctionWrapper*)m_ref)->c_signature = new std::string(signature);
        ((CFunctionWrapper*)m_ref)->c_doc = new std::string(function_doc);
    }
    Object Function::operator() (Tuple args, Dict kwargs) const {
        return New<Object>(PyObject_Call(m_ref, args, kwargs)).INCREF();
    }
} // namespace Py
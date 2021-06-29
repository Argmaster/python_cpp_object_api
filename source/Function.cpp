#include "Function.hh"


namespace Py
{
    namespace _CFunctionType
    {
        void        tp_dealloc(CFunctionObject* self) {
            print("Deallocated");
            if (self->c_function != nullptr)
                delete self->c_function;
            if (self->c_doc != nullptr)
                delete self->c_doc;
            PyObject_GC_UnTrack(self);
            Py_TYPE(self)->tp_free((PyObject*)self);
        }
        int         tp_init(CFunctionObject* self, PyObject* args, PyObject* kwargs) {
            return 0;
        }
        PyObject*   tp_call(PyObject* self, PyObject* args, PyObject* kwargs) {
            return (*((CFunctionObject*)self)->c_function)(
                Old<Object>(self),
                Old<Tuple>(args),
                Old<Dict>(kwargs)
                );
        }
        int         tp_traverse(CFunctionObject* self, visitproc visit, void* args) {
            return 0;
        }
        int         tp_clear(CFunctionObject* self) {
            return 0;
        }
    }
    void init_CFunctionType() {
        if (!_CFunctionType::is_ready) {
            PyType_Ready(&CFunctionType);
            _CFunctionType::is_ready = true;
        }
    }
    Function::Function(
        PyCFunctionT c_function,
        std::string function_doc
    ) : Object(nullptr) {
        init_CFunctionType();
        m_ref = PyObject_Init(PyObject_New(PyObject, &CFunctionType), &CFunctionType);
        ((CFunctionObject*)m_ref)->c_function = new PyCFunctionT(c_function);
        ((CFunctionObject*)m_ref)->c_doc = new std::string(function_doc);
    }
    Object Function::operator() (Tuple args, Dict kwargs) const {
        return New<Object>(PyObject_Call(m_ref, args, kwargs));
    }
} // namespace Py
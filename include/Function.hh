#pragma once
#include "Object.hh"


namespace Py
{
    typedef std::function<Object(Object, Tuple, Dict)> PyCFunctionT;
    struct CFunctionObject
    {
        PyObject_HEAD;
        PyCFunctionT* c_function;
        std::string* c_doc;
    };
    namespace _CFunctionType
    {
        static bool is_ready = false;
        void        tp_dealloc(CFunctionObject* self);
        int         tp_init(CFunctionObject* self, PyObject* args, PyObject* kwargs);
        PyObject*   tp_call(PyObject* self, PyObject* args, PyObject* kwargs);
        int         tp_traverse(CFunctionObject* self, visitproc visit, void* args);
        int         tp_clear(CFunctionObject* self);
    }

    static PyTypeObject CFunctionType{
        .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "CFunctionType",
        .tp_basicsize = sizeof(CFunctionObject),
        .tp_itemsize = 0,
        .tp_dealloc = (destructor)_CFunctionType::tp_dealloc,
        .tp_vectorcall_offset = 0,
        //.tp_getattr
        //.tp_setattr
        //.tp_as_async
        //.tp_repr
        //.tp_as_number
        //.tp_as_sequence
        //.tp_as_mapping
        //.tp_hash
        .tp_call = _CFunctionType::tp_call,
        //.tp_str
        //.tp_getattro
        //.tp_setattro
        //.tp_as_buffer
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
        .tp_doc = "Wrapper object for C functions",
        .tp_traverse = (traverseproc)_CFunctionType::tp_traverse,
        .tp_clear = (inquiry)_CFunctionType::tp_clear,
        //.tp_richcompare
        //.tp_weaklistoffset
        //.tp_iter
        //.tp_iternext
        //.tp_methods
        //.tp_members
        //.tp_getset
        //.tp_base
        //.tp_dict
        //.tp_descr_get
        //.tp_descr_set
        //.tp_dictoffset
        .tp_init = *(initproc*)&_CFunctionType::tp_init,
        //.tp_alloc
        .tp_new = PyType_GenericNew
        //.tp_free
        //.tp_is_gc
        //.tp_bases
        //.tp_mro
        //.tp_cache
        //.tp_subclasses
        //.tp_weaklist
        //.tp_del
        //.tp_version_tag
        //.tp_finalize
        //.tp_vectorcall
    };
    void init_CFunctionType();
    class Function : public Object
    {
    public:
        using Object::Object;
        Function(
            PyCFunctionT c_function,
            std::string function_doc
        );
        /*
            Call a callable Python object 'callable' with arguments given by the
            tuple 'args' and keywords arguments given by the dictionary 'kwargs'.

            'args' must not be NULL, use an empty tuple if no arguments are
            needed. If no named arguments are needed, 'kwargs' can be NULL.

            This is the equivalent of the Python expression:
            callable(*args, **kwargs).
        */
        Object operator () (Tuple args, Dict kwargs) const;
    };
} // namespace Py

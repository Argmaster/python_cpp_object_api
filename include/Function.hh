#pragma once
#include "Object.hh"


namespace Py
{
    typedef std::function<Object(Object, Tuple, Dict)> PyCFunctionT;
    /*
        C type for function wrapper python class
    */
    struct CFunctionWrapper
    {
        PyObject_HEAD;
        PyCFunctionT* c_function;
        std::string* c_signature;
        std::string* c_doc;
    };
    /*
        Namespace for CFunctionWrapperType method definitions
    */
    namespace _CFunctionWrapperType
    {
        static bool is_ready = false;
        // deallocation method, with non-standard members deallocation
        void        tp_dealloc(CFunctionWrapper* self);
        // standard object initialization
        int         tp_init(CFunctionWrapper* self, PyObject* args, PyObject* kwargs);
        // call overload allowing function-like behaviour on python side
        PyObject*   tp_call(PyObject* self, PyObject* args, PyObject* kwargs);
        // stringification function, c_signature and c_doc are contained in it
        PyObject*   tp_str(CFunctionWrapper* self);
        //void        tp_finalize(CFunctionWrapper* self);
    }
    /*
        Function Wrapper python type skeleton
    */
    static PyTypeObject CFunctionWrapperType{
        .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "CFunctionWrapper",
        .tp_basicsize = sizeof(CFunctionWrapper),
        .tp_itemsize = 0,
        .tp_dealloc = (destructor)_CFunctionWrapperType::tp_dealloc,
        //.tp_vectorcall_offset
        //.tp_getattr
        //.tp_setattr
        //.tp_as_async
        .tp_repr = (reprfunc)_CFunctionWrapperType::tp_str,
        //.tp_as_number
        //.tp_as_sequence
        //.tp_as_mapping
        //.tp_hash
        .tp_call = _CFunctionWrapperType::tp_call,
        .tp_str = (reprfunc)_CFunctionWrapperType::tp_str,
        //.tp_getattro
        //.tp_setattro
        //.tp_as_buffer
        .tp_flags = Py_TPFLAGS_DEFAULT,
        .tp_doc = "Wrapper object for C functions",
        //.tp_traverse
        //.tp_clear
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
        .tp_init = (initproc)_CFunctionWrapperType::tp_init,
        //.tp_alloc
        .tp_new = PyType_GenericNew,
        //.tp_free
        //.tp_is_gc
        //.tp_bases
        //.tp_mro
        //.tp_cache
        //.tp_subclasses
        //.tp_weaklist
        //.tp_del
        //.tp_version_tag
        //.tp_finalize = (destructor)_CFunctionWrapperType::tp_finalize
        //.tp_vectorcall
    };
    /*
        Type initialization function, has to be called before type is used for
        the first time, becouse it will fill all the fields with, respectively,
        NULLs and inherited methods
    */
    void init_CFunctionType();
    /*
        Wrapper type for any kind of python callable function, including bound methods
        module level functions, python callable C functions
    */
    class Function : public Object
    {
    public:
        using Object::Object;
        Function(
            PyCFunctionT c_function,
            std::string signature="",
            std::string function_doc=""
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
        std::string Signature() const;
    };
} // namespace Py

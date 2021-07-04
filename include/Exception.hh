#pragma once
#include "Object.hh"


namespace Py
{
    class Exception
    {
    private:
        PyObject* m_type;
        PyObject* m_value;
        PyObject* m_traceback;
        Exception(PyObject* m_type, PyObject* m_value, PyObject* m_traceback);
    public:
        struct Error
        {
            std::string message;
            Error(std::string mess) : message(mess) {}
        };
        // copy constructor
        Exception(const Exception& copied_object);
        // move contructor
        Exception(Exception&& moved_object);
        // destructor
        ~Exception();
        // globally clear exception
        static void Clear();
        // raise exception
        static void Raise(PyObject* _exception_type, std::string _message);
        // raise exception
        static void Raise(PyObject* _exception_type, PyObject* _object);
        // check wheather exception occured and return its type
        static PyObject* Occured();
        // catch exception and return as exception object
        static Exception Catch();
        // raise this exception object
        void Raise();
        // stringify exception
        Py::Str ToStr();
    };
} // namespace Py

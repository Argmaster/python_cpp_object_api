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
            friend std::ostream& operator << (std::ostream& out, Error exc) {
                return out << exc.message;
            }
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
        // check wheather exception occured and return true if had
        static bool HasOccured();
        // check wheather exception not occured and return true if haven't
        static bool HasNotOccured();
        // catch exception and return as exception object
        static Exception Catch();
        // raise this exception object
        void Raise();
        // string representation of exception without traceback
        std::string Exception::StrNoTb();
        // stringify exception
        Py::Str ToStr();
        friend std::ostream& operator << (std::ostream& out, Exception exc);
    };
} // namespace Py

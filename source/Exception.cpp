#include "Exception.hh"

namespace Py
{
    Exception::Exception(PyObject* m_type, PyObject* m_value, PyObject* m_traceback)
        : m_type(m_type), m_value(m_value), m_traceback(m_traceback) {}
    Exception::Exception(const Exception& copied_object)
        : m_type(copied_object.m_type), m_value(copied_object.m_value), m_traceback(copied_object.m_traceback) {
        Py_XINCREF(copied_object.m_type);
        Py_XINCREF(copied_object.m_value);
        Py_XINCREF(copied_object.m_traceback);
    }
    Exception::Exception(Exception&& moved_object)
        : m_type(moved_object.m_type), m_value(moved_object.m_value), m_traceback(moved_object.m_traceback) {
        moved_object.m_type = nullptr;
        moved_object.m_value = nullptr;
        moved_object.m_traceback = nullptr;
    }
    // destructor
    Exception::~Exception() {
        Py_XDECREF(this->m_type);
        Py_XDECREF(this->m_value);
        Py_XDECREF(this->m_traceback);
    }
    void Exception::Clear() {
        PyErr_Clear();
    }
    void Exception::Raise(PyObject* _exception_type, std::string _message) {
        PyErr_SetString(_exception_type, _message.c_str());
        throw Exception::Error(_message);
    }
    void Exception::Raise(PyObject* _exception_type, PyObject* _object) {
        PyErr_SetObject(_exception_type, _object);
        throw Exception::Error(Old<Str>(_object).AsUTF8());
    }
    bool Exception::HasOccured() {
        return PyErr_Occurred() != NULL;
    }
    bool Exception::HasNotOccured() {
        return PyErr_Occurred() == NULL;
    }
    PyObject* Exception::Occured() {
        return PyErr_Occurred();
    }
    Exception Exception::Catch() {
        PyObject* exc_type;
        PyObject* exc_value;
        PyObject* exc_traceback;
        PyErr_Fetch(&exc_type, &exc_value, &exc_traceback);
        PyErr_NormalizeException(&exc_type, &exc_value, &exc_traceback);
        return { exc_type, exc_value, exc_traceback };
    }
    void Exception::Raise() {
        Py_XINCREF(m_type);
        Py_XINCREF(m_value);
        Py_XINCREF(m_traceback);
        PyErr_Restore(m_type, m_value, m_traceback);
        throw Exception::Error(StrNoTb());
    }
    std::string Exception::StrNoTb() {
        return Py::Str("\n").Join(
            Py::Modules::traceback->Call(
                "format_exception_only", {
                    Old<Object>(m_type),
                    Old<Object>(m_value)
                }, {}
        ).As<Py::Str>()).AsUTF8();
    }
    Str Exception::ToStr() {
        if (m_traceback == NULL) {
            return Py::Str("\n").Join(
                Py::Modules::traceback->Call(
                    "format_exception_only", {
                        Old<Object>(m_type),
                        Old<Object>(m_value)
                    }, {}
            ).As<Py::Str>());
        } else {
            return Py::Str("\n").Join(
                Py::Modules::traceback->Call(
                    "format_exception", {
                        Old<Object>(m_type),
                        Old<Object>(m_value),
                        Old<Object>(m_traceback)
                    }, {}
            ).As<Py::Str>());
        }
    }
} // namespace Py

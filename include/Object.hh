#pragma once
#ifdef _DEBUG
#undef _DEBUG
#define _DEBUG_MARKER 1
#endif
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#ifdef _DEBUG_MARKER
#undef _DEBUG_MARKER
#define _DEBUG 1
#endif
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdarg.h>
#include <initializer_list>
#include <utility>
#include <functional>
#include <bitset>
#include <complex>


#ifdef _DEBUG
#define __LOG(info) std::cout << info << std::endl;
#else
#define __LOG(info)
#endif

#define IsNULL(value) if ((value) == NULL) return nullptr;

namespace Py
{
    // Forward declare classes for all basic builtin Python data types
    class Object;
    class Long;
    class Float;
    class Complex;
    class Bool;
    class Str;
    class Bytes;
    class ByteArray;
    class List;
    class Tuple;
    class Dict;
    class Set;
    class FrozenSet;
    class Module;
    class Function;
    class Exception;
    namespace Modules
    {
        extern Module* traceback;
        extern Module* inspect;
        extern Module* json;
    };

#define PyNoneObject Py::Old<Py::Object>(Py_None);
    /*
        Base class for data type classes, provides part of object interface that
        Should be available in every class, eg. type checks
    */
    class Object
    {
    protected:
        /*
            Actuall underlying PyObject, which refcount will be controled */
        PyObject* m_ref = nullptr;
        /*
            Create new object with reference to new PyObject (steal reference) */
        Object(PyObject* py_object);
    public:
        /*
            Copies reference contained by Object, refcount is incremented */
        Object(const Object& copied_object);
        /**
            @brief Moves reference contained by Object, refcount is not incremented */
        Object(Object&& moved_object);
        /*
            Null Initialize
        */
        Object(nullptr_t ptr) : m_ref(nullptr) {}
        /**
            @brief When dies always decrefs underlying PyObject pointer (null-safe) */
        virtual ~Object() {
            Py_XDECREF(m_ref);
        }
        /**
            @brief Construct Wrapper_T out of New PyObject Reference */
        template<typename Wrapper_T>
        friend Wrapper_T New(PyObject* py_new_ref);
        /**
            @brief Construct Wrapper_T out of Borrowed PyObject Reference */
        template<typename Wrapper_T>
        friend Wrapper_T Old(PyObject* py_weak_ref);
        /**
            @brief stream out operator overload */
        friend std::ostream& operator << (std::ostream& os, const Object& py_object);
        /**
            @brief Explicit shortcut for null test */
        inline bool         IsNull() const { return m_ref == NULL; }
        /**
            @brief  Expilcit shortcut for not null test */
        inline bool         IsNotNull() const { return m_ref != NULL; }
        /**
            @brief  Acquire reference count of underlying PyObject */
        inline Py_ssize_t   RefC() const { return Py_REFCNT(m_ref); }
        /**
            @brief Acquire PyObject contained in this Object */
        inline PyObject*    GetRef() const { return m_ref; }
        /**
            @brief Increment reference count of underlying PyObject */
        Object          INCREF() const { Py_XINCREF(m_ref); return *this; };
        /**
            @brief Increment reference count of underlying PyObject */
        Object          operator ++ () const { Py_XINCREF(m_ref); return *this; };
        /**
            @brief Increment reference count of underlying PyObject */
        Object          operator ++ (int) const { Py_XINCREF(m_ref); return *this; };
        /**
            @brief Decrement reference count of underlying PyObject */
        Object          DECREF() const { Py_XDECREF(m_ref); return *this; };
        /**
            @brief Decrement reference count of underlying PyObject */
        Object          operator -- () const { Py_XDECREF(m_ref); return *this; };
        /**
            @brief Decrement reference count of underlying PyObject */
        Object          operator -- (int) const { Py_XDECREF(m_ref); return *this; };
        /* -------------------------------------------------------------------------- */
        /*                 Implicit dynamic casts among wrapper types                 */
        /* -------------------------------------------------------------------------- */
        operator PyObject* () { return m_ref; }
        /**
            @brief Reinterpret object as different type
        */
        template<class cast_type>
        cast_type           As() const { return Old<cast_type>(m_ref); }
        /* -------------------------------------------------------------------------- */
        /*                            Type checks shortcuts                           */
        /* -------------------------------------------------------------------------- */
        inline bool         IsLong() { return PyLong_CheckExact(m_ref); }
        inline bool         IsFloat() { return PyFloat_CheckExact(m_ref); }
        inline bool         IsComplex() { return PyComplex_CheckExact(m_ref); }
        inline bool         IsNumber() { return PyNumber_Check(m_ref); }
        inline bool         IsBool() { return PyBool_Check(m_ref); }
        inline bool         IsStr() { return PyUnicode_CheckExact(m_ref); }
        inline bool         IsBytes() { return PyBytes_CheckExact(m_ref); }
        inline bool         IsByteArray() { return PyByteArray_CheckExact(m_ref); }
        inline bool         IsList() { return PyList_CheckExact(m_ref); }
        inline bool         IsTuple() { return PyTuple_CheckExact(m_ref); }
        inline bool         IsSequence() { return PySequence_Check(m_ref); }
        inline bool         IsBuffer() { return PyObject_CheckBuffer(m_ref); }
        inline bool         IsCallable() { return PyCallable_Check(m_ref); }
        inline bool         IsIterator() { return PyIter_Check(m_ref); }
        inline bool         IsDict() { return PyDict_CheckExact(m_ref); }
        inline bool         IsMapping() { return PyMapping_Check(m_ref); }
        inline bool         IsSet() { return PyAnySet_CheckExact(m_ref); }
        inline bool         IsFrozenSet() { return PyFrozenSet_CheckExact(m_ref); }
        inline bool         IsModule() { return PyModule_CheckExact(m_ref); }
        inline bool         IsFunction() { return PyFunction_Check(m_ref); }
        inline bool         IsCFunction() { return PyCFunction_Check(m_ref); }
        /* -------------------------------------------------------------------------- */
        /*                          Getters, setter, deleters                         */
        /* -------------------------------------------------------------------------- */
        /**
            @brief Returns true if object has attribute attr_name
                This is equivalent to the Python expression hasattr(o, attr_name).
                This function always succeeds.
            @note NOTE, day 07.06.2021, Poland, CPython 3.9.5
                this function has a strange behaviour, likely caused by some caching system,
                that it increments refcount of attr_name however it turns out that if we
                forcibly DECREF object INCREFED by HasAttr, It will very likely cause SEGFAULTS
                in least expected palces
        */
        virtual bool            HasAttr(Str attr_name) const;
        /**
            @brief Retrieve an attribute named attr_name from object o.
            Returns the attribute value on success, or NULL on failure.
            This is the equivalent of the Python expression o.attr_name.
        */
        virtual Object          GetAttr(Str attr_name) const;
        /**
            @brief Set the value of the attribute named attr_name, for object o, to the value v.
                Raise an exception and throw on failure.This is the equivalent of the Python
                statement o.attr_name = v. If v is NULL, the attribute is deleted, however
                this feature is deprecated in favour of using PyObject_DelAttr().
        */
        virtual void            SetAttr(Str attr_name, PyObject* value) const;
        /**
            @brief Delete attribute named attr_name, for object o. Returns -1 on failure.
                This is the equivalent of the Python statement del o.attr_name.
        */
        virtual int             DelAttr(Str attr_name) const;
        /**
            @brief Return element of o corresponding to the object key or NULL on failure.
                This is the equivalent of the Python expression o[key].
        */
        virtual Object          GetItem(Object attr_name) const;
        /**
            @brief Map the object key to the value v. Raise an exception and return -1 on failure;
                return 0 on success.This is the equivalent of the Python statement o[key] = v.
                This function does not steal a reference to v.
        */
        virtual int             SetItem(Object attr_name, PyObject * value) const;
        /**
            @brief Remove the mapping for the object key from the object o. Return -1 on failure.
                This is equivalent to the Python statement del o[key].
        */
        virtual int             DelItem(Object attr_name) const;
        /* -------------------------------------------------------------------------- */
        /*                                 Comparisons                                */
        /* -------------------------------------------------------------------------- */
        /// Less than comparison. This is the equivalent of the Python expression a < b
        int             LessThan(Object other) const;
        /// Less than comparison. This is the equivalent of the Python expression a < b
        int             operator < (Object other) const;
        /// Less or equal comparison. This is the equivalent of the Python expression a <= b
        int             LessEqual(Object other) const;
        /// Less or equal comparison. This is the equivalent of the Python expression a <= b
        int             operator <= (Object other) const;
        /// Equal comparison. This is the equivalent of the Python expression a == b
        int             Equals(Object other) const;
        /// Equal comparison. This is the equivalent of the Python expression a == b
        int             operator == (Object other) const;
        /// Not equal comparison. This is the equivalent of the Python expression a != b
        int             NotEquals(Object other) const;
        /// Not equal comparison. This is the equivalent of the Python expression a != b
        int             operator != (Object other) const;
        /// Greater than comparison. This is the equivalent of the Python expression a > b
        int             GreaterThan(Object other) const;
        /// Greater than comparison. This is the equivalent of the Python expression a > b
        int             operator > (Object other) const;
        /// Greater or equal comparison. This is the equivalent of the Python expression a >= b
        int             GreaterEqual(Object other) const;
        /// Greater or equal comparison. This is the equivalent of the Python expression a >= b
        int             operator >= (Object other) const;
        /* -------------------------------------------------------------------------- */
        /*                             Numerical operators                            */
        /* -------------------------------------------------------------------------- */
        /// Returns the result of adding o1 and o2, or NULL on failure. This is the equivalent of the Python expression o1 + o2
        Object          Add(Object other) const;
        /// Returns the result of adding o1 and o2, or NULL on failure. This is the equivalent of the Python expression o1 + o2
        Object          operator + (Object other) const;
        /// Returns the result of subtracting o2 from o1, or NULL on failure. This is the equivalent of the Python expression o1 - o2.
        Object          Sub(Object other) const;
        /// Returns the result of subtracting o2 from o1, or NULL on failure. This is the equivalent of the Python expression o1 - o2.
        Object          operator - (Object other) const;
        /// Returns the result of multiplying o1 and o2, or NULL on failure. This is the equivalent of the Python expression o1 * o2.
        Object          Mul(Object other) const;
        /// Returns the result of multiplying o1 and o2, or NULL on failure. This is the equivalent of the Python expression o1 * o2.
        Object          operator * (Object other) const;
        /// Returns the result of matrix multiplication on o1 and o2, or NULL on failure. This is the equivalent of the Python expression o1 @ o2.
        Object          MatMul(Object other) const;
        /// Return the floor of o1 divided by o2, or NULL on failure. This is equivalent to the “classic” division of integers
        Object          FloorDiv(Object other) const;
        /**
            @brief Return a reasonable approximation for the mathematical value of o1 divided by o2,
            or NULL on failure. The return value is “approximate” because binary floating point
            numbers are approximate; it is not possible to represent all real numbers in base two.
            This function can return a floating point value when passed two integers.
        */
        Object          TrueDiv(Object other) const;
        /// Shortcut for TrueDiv
        Object          operator / (Object other) const;
        /// Returns the remainder of dividing o1 by o2, or NULL on failure. This is the equivalent of the Python expression o1 % o2.
        Object          Mod(Object other) const;
        /// Returns the remainder of dividing o1 by o2, or NULL on failure. This is the equivalent of the Python expression o1 % o2.
        Object          operator % (Object other) const;
        /// See the built-in function divmod(). Returns NULL on failure. This is the equivalent of the Python expression divmod(o1, o2).
        Object          DivMod(Object other) const;
        /// This is the equivalent of the Python expression o1 ** o2.
        Object          Pow(Object other) const;
        /// Returns the negation of o on success, or NULL on failure. This is the equivalent of the Python expression -o.
        Object          Neg() const;
        /// Returns the negation of o on success, or NULL on failure. This is the equivalent of the Python expression -o.
        Object          operator - () const;
        /// Returns o on success, or NULL on failure. This is the equivalent of the Python expression +o.
        Object          Pos() const;
        /// Returns o on success, or NULL on failure. This is the equivalent of the Python expression +o.
        Object          operator + () const;
        /// Returns the absolute value of o, or NULL on failure. This is the equivalent of the Python expression abs(o).
        Object          Abs() const;
        /// Returns the bitwise negation of o on success, or NULL on failure. This is the equivalent of the Python expression ~o
        Object          Inv() const;
        /// Returns the bitwise negation of o on success, or NULL on failure. This is the equivalent of the Python expression ~o
        Object          operator ~ () const;
        /// Returns the result of left shifting o1 by o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 << o2.
        Object          LShift(Object other) const;
        /// Returns the result of left shifting o1 by o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 << o2.
        Object          operator << (Object other) const;
        /// Returns the result of right shifting o1 by o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 >> o2.
        Object          RShift(Object other) const;
        /// Returns the result of right shifting o1 by o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 >> o2.
        Object          operator >>(Object other) const;
        /// Returns the “bitwise and” of o1 and o2 on success and NULL on failure. This is the equivalent of the Python expression o1 & o2.
        Object          And(Object other) const;
        /// Returns the “bitwise and” of o1 and o2 on success and NULL on failure. This is the equivalent of the Python expression o1 & o2.
        Object          operator & (Object other) const;
        /// Returns the “bitwise or” of o1 and o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 | o2.
        Object          Or(Object other) const;
        /// Returns the “bitwise or” of o1 and o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 | o2.
        Object          operator | (Object other) const;
        /// Returns the “bitwise exclusive or” of o1 by o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 ^ o2.
        Object          Xor(Object other) const;
        /// Returns the “bitwise exclusive or” of o1 by o2 on success, or NULL on failure. This is the equivalent of the Python expression o1 ^ o2.
        Object          operator ^ (Object other) const;
        /* -------------------------------------------------------------------------- */
        /*                       Type operations and conversions                      */
        /* -------------------------------------------------------------------------- */
        /**
            @brief Compute a string representation of object o. Returns the string
                representation on success, NULL on failure.This is the equivalent of the
                Python expression repr(o).Called by the repr() built - in function.
        */
        Str             Repr() const;
        /**
            @brief  Same as Repr, but returns C++ string
        */
        std::string     ReprCStr() const;
        /**
            @brief As PyObject_Repr(), compute a string representation of object o,
                but escape the non-ASCII characters in the string returned by PyObject_Repr()
                with \x, \u or \U escapes. This generates a string similar to that returned by
                PyObject_Repr() in Python 2. Called by the ascii() built-in function.
        */
        Str             ASCII() const;
        /**
            @brief Compute a string representation of object o. Returns the string representation
                on success, NULL on failure. This is the equivalent of the Python expression
                str(o). Called by the str() built-in function and, therefore, by the print()
                function.
        */
        Str             ToStr() const;
        /**
            @brief Compute a bytes representation of object o. NULL is returned on failure
                and a bytes object on success.This is equivalent to the Python expression
                bytes(o), when o is not an integer.Unlike bytes(o), a TypeError is raised
                when o is an integer instead of a zero - initialized bytes object.
        */
        Bytes           ToBytes() const;
        /**
            @brief Compute and return the hash value of an object o. On failure, return -1.
                This is the equivalent of the Python expression hash(o).
        */
        Py_hash_t       Hash() const;
        /**
            @brief Returns 1 if the object o is considered to be true, and 0 otherwise.
                This is equivalent to the Python expression not not o.On failure, return -1.
        */
        bool            IsTrue() const;
        /**
            @brief Returns 0 if the object o is considered to be true, and 1 otherwise.
                This is equivalent to the Python expression not o. On failure, return -1
        */
        bool            Not() const;
        /**
            @brief Return the length of object o. If the object o provides either the
            sequence and mapping protocols, the sequence length is returned.
            On error, -1 is returned.This is the equivalent to the Python expression len(o).
        */
        virtual Py_ssize_t Size() const;
        /**
            @brief Return the length of object o. If the object o provides either the
                sequence and mapping protocols, the sequence length is returned.
                On error, -1 is returned.This is the equivalent to the Python expression len(o).
        */
        virtual Py_ssize_t Length() const;
        /**
            @brief This is equivalent to the Python expression iter(o). It returns a new iterator
                for the object argument, or the object itself if the object is already an iterator.
                Raises TypeError and returns NULL if the object cannot be iterated.
        */
        Object          Iter() { return PyObject_GetIter(m_ref); }
        /**
            Call a callable Python object with arguments given by the
            tuple 'args' and keywords arguments given by the dictionary 'kwargs'.

            'args' must not be NULL, use an empty tuple if no arguments are
            needed. If no named arguments are needed, 'kwargs' can be NULL.

            This is the equivalent of the Python expression:
            callable(*args, **kwargs).
        */
        Object          Call(Tuple args, Dict kwargs);
        /**
            Call function retreived with GetAttr by name with arguments given by the
            tuple 'args' and keywords arguments given by the dictionary 'kwargs'.

            'args' must not be NULL, use an empty tuple if no arguments are
            needed. If no named arguments are needed, 'kwargs' can be NULL.

            This is the equivalent of the Python expression:
            callable(*args, **kwargs).
        */
        Object          Call(std::string name, Tuple args, Dict kwargs);
        /* -------------------------------------------------------------------------- */
        /*                           Type checks and friends                          */
        /* -------------------------------------------------------------------------- */
        /**
            @brief Return 1 if the class derived is identical to or derived from the class cls,
                otherwise return 0. In case of an error, return -1.
                If cls is a tuple, the check will be done against every entry in cls.
                The result will be 1 when at least one of the checks returns 1, otherwise it will be 0.
        */
        int             IsSubclass(Object cls) const { return PyObject_IsSubclass(m_ref, cls); }
        /**
            @brief Return 1 if inst is an instance of the class cls or a subclass of cls, or 0 if not.
                On error, returns - 1 and sets an exception.
                If cls is a tuple, the check will be done against every entry in cls.
                The result will be 1 when at least one of the checks returns 1, otherwise it will be 0.
        */
        int             IsInstance(Object cls) const { return PyObject_IsInstance(m_ref, cls); }
        /**
            @brief When o is non-NULL, returns a type object corresponding to the object type of object o.
                On failure, raises SystemError and returns NULL. This is equivalent to the Python
                expression type(o). This function increments the reference count of the return value.
                There’s really no reason to use this function instead of the common expression
                o->ob_type, which returns a pointer of type PyTypeObject*, except when the incremented
                reference count is needed.
        */
        Object          Type() const { return PyObject_Type(m_ref); }
        /**
            @brief Return true if the object o is of type type or a subtype of type.Both parameters must be non - NULL.
        */
        bool            TypeCheck(PyTypeObject* py_type) const { return PyObject_TypeCheck(m_ref, py_type); }
        /**
            @brief This is equivalent to the Python expression dir(o), returning a (possibly empty)
                list of strings appropriate for the object argument, or NULL if there was an error.
                If the argument is NULL, this is like the Python dir(), returning the names of the
                current locals; in this case, if no execution frame is active then NULL is returned
                but PyErr_Occurred() will return false.
        */
        Object          Dir() { return PyObject_Dir(m_ref); }
    };
    /**
        @brief Create Python Object wrapper from PyObject* new reference (counted)
    */
    template<typename Wrapper_T>
    Wrapper_T New(PyObject* py_new_ref) {
        return Wrapper_T(py_new_ref);
    }
    /**
        @brief Create Python Object wrapper from PyObject* weak reference (not counted/owned by sb else)
    */
    template<typename Wrapper_T>
    Wrapper_T Old(PyObject* py_weak_ref) {
        Py_XINCREF(py_weak_ref);
        return Wrapper_T(py_weak_ref);
    }
    template<typename T, typename... Args>
    void print(T param, Args... args) {
        std::cout << param << " ";
        print(args...);
    }
    template<typename T>
    void print(T param) {
        std::cout << param << std::endl;
    }
} // namespace Py

#include "Exception.hh"
#include "Long.hh"
#include "Float.hh"
#include "Complex.hh"
#include "Bool.hh"
#include "Str.hh"
#include "Bytes.hh"
#include "ByteArray.hh"
#include "List.hh"
#include "Tuple.hh"
#include "Dict.hh"
#include "Set.hh"
#include "FrozenSet.hh"
#include "Module.hh"
#include "Function.hh"

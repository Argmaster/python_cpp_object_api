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


#ifdef _DEBUG
#define __LOG(info) std::cout << info << std::endl;
#else
#define __LOG(info)
#endif


namespace Py
{
    // Forward declare classes for all basic builtin Python data types
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
    // Base class for data type classes, provides part of object interface that
    // Should be available in every class, eg. type checks
    class Object
    {
    protected:
        // Actuall underlying PyObject, which refcount will be controled
        PyObject* m_ref = nullptr;
        /// Assume that pointer given is a new reference
        Object(PyObject* py_object)
            : m_ref(py_object) {
            __LOG("Object New!");
        }
    public:
        /// Copies reference contained by Object, refcount is incremented
        Object(const Object& moved_object)
            : m_ref(moved_object.m_ref) {
            Py_XINCREF(moved_object.m_ref);
            __LOG("Object Copied!");
        }
        /// Moves reference contained by Object, refcount is not incremented
        Object(Object&& moved_object)
            : m_ref(moved_object.m_ref) {
            moved_object.m_ref = nullptr;
            //Py_XINCREF(moved_object.m_ref);
            __LOG("Object Moved!");
        }
        /// When dies always decrefs underlying PyObject pointer (null-safe)
        virtual ~Object() {
#ifdef _DEBUG
            if (IsNotNull())
                __LOG("Object DECREF! " << RefC() << " (-1)");
#endif
            Py_XDECREF(m_ref);
        }
        /// Construct Str out of New PyObject Reference
        template<typename Wrapper_T>
        friend Wrapper_T FromNew(PyObject* py_new_ref); // ! new reference construction
        /// Construct Str out of Borrowed PyObject Reference
        template<typename Wrapper_T>
        friend Wrapper_T FromOld(PyObject* py_weak_ref); // ? borrowed reference construction
        // Explicit shortcut for null test
        inline bool         IsNull() const { return m_ref == NULL; }
        // Expilcit shortcut for not null test
        inline bool         IsNotNull() const { return m_ref != NULL; }
        /// Acquire reference count of underlying PyObject
        inline Py_ssize_t   RefC() const { return Py_REFCNT(m_ref); }
        inline PyObject*    GetRef() const { return m_ref; }
        /* -------------------------------------------------------------------------- */
        /*                 Implicit dynamic casts among wrapper types                 */
        /* -------------------------------------------------------------------------- */
        operator PyObject* () { return m_ref; }
        operator bool() const { return PyObject_IsTrue(m_ref); }
        operator Object ();
        operator Long ();
        operator Float ();
        operator Complex ();
        operator Bool ();
        operator Str ();
        operator Bytes ();
        operator ByteArray ();
        operator List ();
        operator Tuple ();
        operator Dict ();
        operator Set ();
        operator FrozenSet ();
        template<class cast_type>
        cast_type           As() { return FromOld<cast_type>(m_ref); }
        /* -------------------------------------------------------------------------- */
        /*                            Type checks shortcuts                           */
        /* -------------------------------------------------------------------------- */
        inline bool         IsLong() { return PyLong_CheckExact(m_ref); }
        inline bool         IsFloat() { return PyFloat_CheckExact(m_ref); }
        inline bool         IsComplex() { return PyComplex_CheckExact(m_ref); }
        inline bool         IsBool() { return PyBool_Check(m_ref); }
        inline bool         IsStr() { return PyUnicode_CheckExact(m_ref); }
        inline bool         IsBytes() { return PyBytes_CheckExact(m_ref); }
        inline bool         IsByteArray() { return PyByteArray_CheckExact(m_ref); }
        inline bool         IsList() { return PyList_CheckExact(m_ref); }
        inline bool         IsTuple() { return PyTuple_CheckExact(m_ref); }
        inline bool         IsDict() { return PyDict_CheckExact(m_ref); }
        inline bool         IsSet() { return PyAnySet_CheckExact(m_ref); }
        inline bool         IsFrozenSet() { return PyFrozenSet_CheckExact(m_ref); }

        /* -------------------------------------------------------------------------- */
        /*                        Python C API Object Protocol                        */
        /* -------------------------------------------------------------------------- */
        /* -------------------------------------------------------------------------- */
        /*                          Getters, setter, deleters                         */
        /* -------------------------------------------------------------------------- */
        // Returns true if object has attribute attr_name
        // This is equivalent to the Python expression hasattr(o, attr_name).
        // This function always succeeds.
        // -----------------------------------------------------------------------------
        // ! NOTE, day 07.06.2021, Poland, CPython 3.9.5
        // ! this function has a strange behaviour, likely caused by some caching system,
        // ! that it increments refcount of attr_name however it turns out that if we
        // ! forcibly DECREF object INCREFED by HasAttr, It will very likely cause SEGFAULTS
        // ! in least expected palces, eg. PyUnicode_FromString turned out to be failing becouse of it!
        bool            HasAttr(Str attr_name) const;
        // Retrieve an attribute named attr_name from object o.
        // Returns the attribute value on success, or NULL on failure.
        // This is the equivalent of the Python expression o.attr_name.
        Object          GetAttr(Str attr_name) const;
        // Set the value of the attribute named attr_name, for object o, to the value v.
        // Raise an exception and return -1 on failure; return 0 on success.This is the
        // equivalent of the Python statement o.attr_name = v.
        // If v is NULL, the attribute is deleted, however this feature is deprecated in
        // favour of using PyObject_DelAttr().
        int             SetAttr(Str attr_name, PyObject* value) const;
        // Delete attribute named attr_name, for object o. Returns -1 on failure.
        // This is the equivalent of the Python statement del o.attr_name.
        int             DelAttr(Str attr_name) const;
        // Return element of o corresponding to the object key or NULL on failure.
        // This is the equivalent of the Python expression o[key].
        Object          GetItem(Str attr_name) const;
        // Map the object key to the value v. Raise an exception and return -1 on failure;
        // return 0 on success.This is the equivalent of the Python statement o[key] = v.
        // This function does not steal a reference to v.
        int             SetItem(Str attr_name, PyObject * value) const;
        // Remove the mapping for the object key from the object o. Return -1 on failure.
        // This is equivalent to the Python statement del o[key].
        int             DelItem(Str attr_name) const;
        /* -------------------------------------------------------------------------- */
        /*                                 Comparisons                                */
        /* -------------------------------------------------------------------------- */
        /// Less than comparison. This is the equivalent of the Python expression a < b
        Bool            LT(Object other) const;
        /// Less than comparison. This is the equivalent of the Python expression a < b
        Bool            operator < (Object other) const;
        /// Less or equal comparison. This is the equivalent of the Python expression a <= b
        Bool            LE(Object other) const;
        /// Less or equal comparison. This is the equivalent of the Python expression a <= b
        Bool            operator <= (Object other) const;
        /// Equal comparison. This is the equivalent of the Python expression a == b
        Bool            EQ(Object other) const;
        /// Equal comparison. This is the equivalent of the Python expression a == b
        Bool            operator == (Object other) const;
        /// Not equal comparison. This is the equivalent of the Python expression a != b
        Bool            NE(Object other) const;
        /// Not equal comparison. This is the equivalent of the Python expression a != b
        Bool            operator != (Object other) const;
        /// Greater than comparison. This is the equivalent of the Python expression a > b
        Bool            GT(Object other) const;
        /// Greater than comparison. This is the equivalent of the Python expression a > b
        Bool            operator > (Object other) const;
        /// Greater or equal comparison. This is the equivalent of the Python expression a >= b
        Bool            GE(Object other) const;
        /// Greater or equal comparison. This is the equivalent of the Python expression a >= b
        Bool            operator >= (Object other) const;
        /* -------------------------------------------------------------------------- */
        /*                       Type operations and conversions                      */
        /* -------------------------------------------------------------------------- */
        // Compute a string representation of object o. Returns the string
        // representation on success, NULL on failure.This is the equivalent of the
        // Python expression repr(o).Called by the repr() built - in function.
        Str             Repr() const;
        // As PyObject_Repr(), compute a string representation of object o,
        // but escape the non-ASCII characters in the string returned by PyObject_Repr()
        // with \x, \u or \U escapes. This generates a string similar to that returned by
        // PyObject_Repr() in Python 2. Called by the ascii() built-in function.
        Str             ASCII() const;
        // Compute a string representation of object o. Returns the string representation
        // on success, NULL on failure. This is the equivalent of the Python expression
        // str(o). Called by the str() built-in function and, therefore, by the print()
        // function.
        Str             ToStr() const;
        // Compute a bytes representation of object o. NULL is returned on failure
        // and a bytes object on success.This is equivalent to the Python expression
        // bytes(o), when o is not an integer.Unlike bytes(o), a TypeError is raised
        // when o is an integer instead of a zero - initialized bytes object.
        Bytes           ToBytes() const;
        // Compute and return the hash value of an object o. On failure, return -1.
        // This is the equivalent of the Python expression hash(o).
        Py_hash_t       Hash() const;
        // Returns 1 if the object o is considered to be true, and 0 otherwise.
        // This is equivalent to the Python expression not not o.On failure, return -1.
        bool            IsTrue() const;
        // Returns 0 if the object o is considered to be true, and 1 otherwise.
        // This is equivalent to the Python expression not o. On failure, return -1
        bool            Not() const;
        // Return the length of object o. If the object o provides either the
        // sequence and mapping protocols, the sequence length is returned.
        //On error, -1 is returned.This is the equivalent to the Python expression len(o).
        Py_ssize_t      Size() const;
        // Return the length of object o. If the object o provides either the
        // sequence and mapping protocols, the sequence length is returned.
        //On error, -1 is returned.This is the equivalent to the Python expression len(o).
        Py_ssize_t      Length() const;
        /* -------------------------------------------------------------------------- */
        /*                           Type checks and friends                          */
        /* -------------------------------------------------------------------------- */
        // Return 1 if the class derived is identical to or derived from the class cls,
        // otherwise return 0. In case of an error, return -1.
        // If cls is a tuple, the check will be done against every entry in cls.
        // The result will be 1 when at least one of the checks returns 1, otherwise it will be 0.
        int             IsSubclass(PyObject* cls) const { return PyObject_IsSubclass(m_ref, cls); }
        // Return 1 if inst is an instance of the class cls or a subclass of cls, or 0 if not.
        // On error, returns - 1 and sets an exception.
        // If cls is a tuple, the check will be done against every entry in cls.
        // The result will be 1 when at least one of the checks returns 1, otherwise it will be 0.
        int             IsInstance(PyObject* cls) const { return PyObject_IsInstance(m_ref, cls); }
        // When o is non-NULL, returns a type object corresponding to the object type of object o.
        // On failure, raises SystemError and returns NULL. This is equivalent to the Python
        // expression type(o). This function increments the reference count of the return value.
        // There’s really no reason to use this function instead of the common expression
        // o->ob_type, which returns a pointer of type PyTypeObject*, except when the incremented
        // reference count is needed.
        Object          Type() const { return PyObject_Type(m_ref); }
        // Return true if the object o is of type type or a subtype of type.Both parameters must be non - NULL.
        bool            TypeCheck(PyTypeObject* py_type) const { return PyObject_TypeCheck(m_ref, py_type); }
        /* -------------------------------------------------------------------------- */
        /*              Those two who do not match any category above...              */
        /* -------------------------------------------------------------------------- */
        // This is equivalent to the Python expression dir(o), returning a (possibly empty)
        // list of strings appropriate for the object argument, or NULL if there was an error.
        // If the argument is NULL, this is like the Python dir(), returning the names of the
        // current locals; in this case, if no execution frame is active then NULL is returned
        // but PyErr_Occurred() will return false.
        Object          Dir() { return PyObject_Dir(m_ref); }
        // This is equivalent to the Python expression iter(o). It returns a new iterator
        // for the object argument, or the object itself if the object is already an iterator.
        // Raises TypeError and returns NULL if the object cannot be iterated.
        Object          Iter() { return PyObject_GetIter(m_ref); }
    };
    template<typename Wrapper_T>
    Wrapper_T FromNew(PyObject* py_new_ref) { return Wrapper_T(py_new_ref); }
    template<typename Wrapper_T>
    Wrapper_T FromOld(PyObject* py_weak_ref) { Py_XINCREF(py_weak_ref); return Wrapper_T(py_weak_ref); }
} // namespace Py


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

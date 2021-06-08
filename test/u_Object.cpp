#include "Object.hh"
#include <assert.h>

// construction tests
void test_1()
{
    Py::Object o = Py::Object::FromNew(PyUnicode_FromString("object"));
    {
        assert(o.RefC() == 1);
        Py::Object o2(o);
        assert(o.RefC() == 2);
        Py::Object o3(Py::Object::FromOld(o));
        assert(o.RefC() == 3);
    }
    //std::cout << o.RefC() << std::endl;
    assert(o.RefC() == 1);
}
// casting tests
void test_2()
{
    Py::Object o = Py::Object::FromNew(PyUnicode_FromString("object"));
    // It turns out Its quite easy to get memory leaks here
    assert(o.HasAttr(o) == 0);
    assert(o.RefC() == 1);
    // implicit conversion, thus constructs weak reference
    Py::Str str_o = o;
    //std::cout << o.RefC() << std::endl;
    assert(o.RefC() == 2);
    // same thing here
    assert(o.HasAttr(o.As<Py::Str>()) == 0);
    assert(o.RefC() == 1);
}
// method tests
void test_3()
{
    Py::Object o = Py::Object::FromNew(PyUnicode_FromString("object"));
    assert(o.IsBool() == 0);
    assert(o.IsByteArray() == 0);
    assert(o.IsBytes() == 0);
    assert(o.IsComplex() == 0);
    assert(o.IsDict() == 0);
    assert(o.IsFloat() == 0);
    assert(o.IsFrozenSet() == 0);
    assert(o.IsList() == 0);
    assert(o.IsLong() == 0);
    assert(o.IsNull() == 0);
    assert(o.IsSet() == 0);
    assert(o.IsStr() == 1);
    assert(o.IsTrue() == 1);
    assert(o.IsTuple() == 0);
}
// other ops tests
void test_4()
{
    Py::Object o2 = Py::Str::New("Koteu");
    std::cout << o2.As<Py::Str>().AsUTF8() << std::endl;
    Py::Object o1 = Py::Str::New("Ala");

    //assert((o1 > o2) == true);
    //assert((o1 < o2) == false);
}

int main(int argc, char* argv[], char* env[])
{
    Py_Initialize();
    auto index = argc > 1 ? atoi(argv[1]) : -1;
    switch (index) {
        case(1):
        {
            test_1();
            break;
        }
        case(2):
        {
            test_2();
            break;
        }
        case(3):
        {
            test_3();
            break;
        }
        case(4):
        {
            test_4();
            break;
        }
        default:
        {
            test_1();
            test_2();
            test_3();
            test_4();
            break;
        }
    }
    Py_Finalize();
    return 0;
}
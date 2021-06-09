#include "Object.hh"
#include <assert.h>

// construction tests
void test_1()
{
    Py::Object o = Py::New<Py::Object>(PyUnicode_FromString("object"));
    {
        assert(o.RefC() == 1);
        Py::Object o2(o);
        assert(o.RefC() == 2);
        Py::Object o3(Py::Old<Py::Object>(o));
        assert(o.RefC() == 3);
    }
    assert(o.RefC() == 1);
}
// casting tests
void test_2()
{
    Py::Object o = Py::New<Py::Object>(PyUnicode_FromString("object"));
    Py::Str str_o = o;
    assert(o.RefC() == 2);
    assert(str_o.RefC() == 2);
    Py::Str str_o2 = o.As<Py::Str>();
    assert(o.RefC() == 3);
    assert(str_o.RefC() == 3);
}
// method tests
void test_3()
{
    {
        Py::Object o = Py::New<Py::Object>(PyUnicode_FromString("object"));
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
        assert(o.RefC() == 1);
    }
    Py::Object o1 = Py::Str("__doc__");
    Py::Object o2 = Py::Str("__ge__");
    {
        auto attr = o1.HasAttr(o1);
        assert(attr);
    }
    {
        auto attr = o1.GetAttr(o1);
        assert(attr.IsNotNull());
    }
    {
        auto attr = o1.SetAttr(o1, o2);
        assert(attr == -1);
        PyErr_Clear();
    }
    {
        auto attr = o1.DelAttr(o1);
        assert(attr == -1);
        PyErr_Clear();
    }
    {
        auto attr = o1.GetItem(o1);
        assert(attr.IsNull());
        PyErr_Clear();
    }
    {
        auto attr = o1.SetItem(o1, o2);
        assert(attr == -1);
        PyErr_Clear();
    }
    {
        auto attr = o1.DelItem(o1);
        assert(attr == -1);
        PyErr_Clear();
    }
    {
        assert(o1.__lt__(o2) == true);
        assert((o1 < o2) == true);
        assert(o1.__le__(o2) == true);
        assert((o1 <= o2) == true);
        assert(o1.__eq__(o2) == false);
        assert((o1 == o2) == false);
        assert(o1.__eq__(o1) == true);
        assert((o1 == o1) == true);
        assert(o1.__ne__(o2) == true);
        assert((o1 != o2) == true);
        assert(o1.__ne__(o1) == false);
        assert((o1 != o1) == false);
        assert(o1.__gt__(o2) == false);
        assert((o1 > o2) == false);
        assert(o1.__ge__(o2) == false);
        assert((o1 >= o2) == false);
        assert((o1 == o2) == false);
    }
    {
        assert(o1.Repr().IsNotNull());
        assert((o1.Repr().AsUTF8() == "'__doc__'"));
        assert(o1.ToStr().IsNotNull());
        assert((o1.ToStr().AsUTF8() == "__doc__"));
        assert(o1.ToBytes().IsNull()); PyErr_Clear();
    }
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
        default:
        {
            test_1();
            test_2();
            test_3();
            break;
        }
    }
    Py_Finalize();
    return 0;
}
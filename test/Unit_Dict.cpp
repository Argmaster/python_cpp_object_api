#include <Dict.hh>
#include <assert.h>

void test_1()
{
    Py::Dict dict({
        { "key", Py::Long(1) },
                  { "not key at all", Py::List({ Py::Long(1), Py::Float(2), Py::Complex(3, 3) }) },
                  { "unlikely key", Py::Float(333) }
                  });
    assert(dict.ToStr() == "{'key': 1, 'not key at all': [1, 2.0, (3+3j)], 'unlikely key': 333.0}");
    for (auto key : dict.Keys().Sort()) {
        __LOG(dict.GetItem(key.As<Py::Str>()));
    }
}
void test_2()
{
    Py::Dict dict1({
        { "key", Py::Long(1) },
                   });
    Py::Dict dict2({
        { "unlikely key", Py::Float(333) }
                   });
    dict2.SetItem(
        "not key at all",
        Py::List({ Py::Long(1), Py::Float(2), Py::Complex(3, 3) })
    );
    assert(dict1.Update(dict2) == 0);
    assert(dict1.ToStr() == "{'key': 1, 'unlikely key': 333.0, 'not key at all': [1, 2.0, (3+3j)]}");
    assert(dict1.Keys().Length() == 3);
    assert(dict1.Values().Length() == 3);
    assert(dict1.DelItem("unlikely key") == 0);
    assert(dict1.Items().Length() == 2);
    assert(dict1.Contains(Py::Str("key")) == 1);
    dict1.Clear();
    assert(dict1.Length() == 0);
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
        default:
        {
            test_1();
            test_2();
            break;
        }
    }
    Py_Finalize();
    return 0;
}
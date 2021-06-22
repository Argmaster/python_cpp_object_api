#include "List.hh"
#include <assert.h>

void test_1()
{
    auto list = Py::List({ Py::Str("Ala"), Py::Long(11), Py::Long(-2434), Py::Float(0.3333) });
    assert(list.ToStr() == "['Ala', 11, -2434, 0.3333]");
}
void test_2()
{
    auto ll = Py::Long(-2434);
    auto list = Py::List({ Py::Str("Ala"), Py::Long(11), ll, Py::Float(0.3333) });
    assert(ll.RefC() == 2);
    assert(list.GetSlice(1, 3).ToStr() == "[11, -2434]");
    assert(ll.RefC() == 2);
    auto e = list[{1, 3}];
    assert(ll.RefC() == 3);
    assert(e == list.GetSlice(1, 3));
    assert(ll.RefC() == 3);
    assert(list.SetSlice(1, 3, list.GetSlice(1, 3)) == 0);
    assert(ll.RefC() == 3);
    assert(list.GetItem(3).ToStr() == "0.3333");
    assert(list.GetItem(3).ToStr() == list[3].ToStr());
    assert(list.SetItem(3, Py::Str("Cat")) == 0);
    assert(list.GetItem(3).ToStr() == "Cat");
    assert(list.Length() == 4);
    assert(list.Size() == 4);
    int i = 0;
    for (auto e : list) {
        assert(e == list.GetItem(i));
        i++;
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
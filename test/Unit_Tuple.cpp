#include "Tuple.hh"
#include <assert.h>

void test_1()
{
    auto tuple = Py::Tuple({ Py::Str("Ala"), Py::Long(11), Py::Long(-2434), Py::Float(0.3333) });
    assert(tuple.ToStr() == "('Ala', 11, -2434, 0.3333)");
}
void test_2()
{
    auto tuple = Py::Tuple({ Py::Str("Ala"), Py::Long(11), Py::Long(-2434), Py::Float(0.3333) });
    assert(tuple.GetSlice(1, 3).ToStr() == "(11, -2434)");
    assert(tuple.GetItem(3).ToStr() == "0.3333");
    assert(tuple.GetItem(3).ToStr() == tuple[3].ToStr());
    assert(tuple.SetItem(3, Py::Str("Cat")) == 0);
    assert(tuple.GetItem(3).ToStr() == "Cat");
    assert(tuple.Length() == 4);
    assert(tuple.Size() == 4);
    int i = 0;
    for (auto e : tuple) {
        assert(e == tuple.GetItem(i));
        i++;
    }
    assert(tuple.Index(Py::Str("Ala")) == 0);
    assert(tuple.Count(Py::Str("Ala")) == 1);
    assert(tuple.Contains(Py::Str("Cat")) == 1);
    auto tuple1 = Py::Tuple({ Py::Str("Ala") });
    auto tuple2 = Py::Tuple({ Py::Long(11), Py::Long(-2434), Py::Float(0.3333) });
    assert(tuple1 + tuple2 == tuple1.Concat(tuple2));
    assert((tuple1 + tuple2).Length() == 4);
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
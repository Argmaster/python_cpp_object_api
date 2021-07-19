#include "Module.hh"
#include <assert.h>

void test_1()
{
    auto json = Py::Module::Import("json");
    assert(json.Symbols().Length() == 26);
    assert(json.RefC() == 2);
    auto json2 = Py::Module::Import("json");
    assert(json2.RefC() == 3);
    assert(json.RefC() == 3);
}
void test_2()
{
    auto json = Py::Module::Import("json");
    __LOG(json.Call("dumps", {Py::Dict({{"Key", Py::Float(0.333)}})}, nullptr))
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
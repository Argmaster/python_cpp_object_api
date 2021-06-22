#include "Module.hh"
#include <assert.h>

void test_1()
{
    auto json = Py::Module::Import("json");
    assert(json.Symbols().Length() == 26);
    __LOG(json.RefC());
    auto json2 = Py::Module::Import("json");
    __LOG(json2.RefC());
    __LOG(json.RefC());
}
void test_2()
{
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
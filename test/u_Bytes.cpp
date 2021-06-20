#include "Str.hh"
#include <assert.h>

void test_1()
{
    auto str = Py::Bytes("Ala");
    assert(str.Length() == 3);
    assert(str.AsString() == "Ala");
    Py::Str unic = str.Decode("utf-8");
    assert(unic.AsUTF8() == "Ala");
    __LOG("Finished");
}
void test_2()
{
    auto str = Py::Bytes("Moj ");
    str.Push("Koteu");
    assert(str.AsString() == "Moj Koteu");
    assert(str.Decode("utf-8") == "Moj Koteu");
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
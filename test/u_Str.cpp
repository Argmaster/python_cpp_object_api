#include "Str.hh"
#include <assert.h>

void test_1()
{
    {
        Py::Str str("Ala");
        assert(str.RefC() == 1);
    }
    {
        auto str = Py::Str::FromFormat("Some num: %i and %lu", 1, 2);
        assert(str.AsUTF8() == "Some num: 1 and 2");
        __LOG(str)
    }
}
void test_2()
{
    auto str = Py::Str("Ala");
    auto bytes = str.Encode("utf-8");
    assert(str.AsUTF8() == std::string("Ala"));
    auto str_2 = Py::Str::Decode("some encoded source", "ascii");
    auto bytes_2 = str_2.Encode("ascii");
    assert(str_2.AsUTF8() == std::string("some encoded source"));
    assert(str_2.AsUTF8() == bytes_2.AsString());
}
void test_3()
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
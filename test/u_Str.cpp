#include "Str.hh"
#include <assert.h>

void test_1()
{
    auto str = Py::Str::New("Ala");
}
void test_2()
{
}
void test_3()
{
}
void test_4()
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
#include "Str.hh"
#include <assert.h>

void test_1()
{
    auto str = Py::Bytes::New("Ala");
    __LOG(str);
}
void test_2()
{
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
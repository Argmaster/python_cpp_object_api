#include <Dict.hh>
#include <assert.h>

void test_1()
{
    Py::Dict dict({
        {  "key", Py::Long(1) }
                  });
    std::cout << dict << std::endl;
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
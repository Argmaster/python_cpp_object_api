#include "Function.hh"
#include <assert.h>

Py::Object func(
    Py::Object self,
    Py::Tuple args,
    Py::Dict kwargs
) {
    Py::print("Hello there im here");
    Py::print(args);
    Py::print(kwargs);
    return Py::Tuple({});
}

void test_1()
{
    {
        Py::Function pyfunc(func, "some function here");
        Py::print("Hi there");
        Py::print(pyfunc);
        Py::print(pyfunc({ Py::Long(11) }, { { "kot", Py::Long(123) } }));
    }
    Py::print("After dealloc");
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
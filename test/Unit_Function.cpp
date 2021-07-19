#include "Function.hh"
#include <assert.h>


void test_1()
{
    Py::Function pyfunc([](
        Py::Object self,
        Py::Tuple args,
        Py::Dict kwargs
        )
        {
            Py::print(args);
            Py::print(kwargs);
            return Py::Tuple({});
        }, "show(*args, **kwargs)");
    Py::print(pyfunc);
    Py::print(pyfunc({ Py::Long(11) }, { { "kot", Py::Long(123) } }));

}
void test_2()
{
    Py::Function pyfunc([](
        Py::Object self,
        Py::Tuple args,
        Py::Dict kwargs
        ) -> Py::Object
        {
            Py::print("Second call");
            PyObject* a;
            PyObject* b;
            IsNULL(args.ParseTuple("OO", &a, &b));
            auto wa = Py::Old<Py::Long>(a);
            auto wb = Py::Old<Py::Long>(b);
            Py::print(wa);
            Py::print(wb);
            return wa + wb;
        }, "add(a: int, b: int)");
    Py::print(pyfunc);
    Py::print(pyfunc({ Py::Long(11), Py::Float(13) }, nullptr));
    Py::print("Finalized");
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
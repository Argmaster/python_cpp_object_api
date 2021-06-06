#include "Object.hh"
#include <assert.h>
#include <iostream>
#include <vector>
#include <string>


void construction()
{
    {
        Py::Object o = Py::Object::FromNew(PyUnicode_FromString("object"));

        assert(o.HasAttr(o) == 0);
        assert(o.RefC() == 2);
        std::cout << o.Type() << std::endl;
        std::cout << o.Repr().AsUTF8() << std::endl;
    }
}


int main(int argc, char* argv[], char* env[])
{
    Py_Initialize();
    switch (argc > 1 ? atoi(argv[0]) : -1) {
        case(1):
        {
            construction();
            break;
        }
        default:
            construction();
    }
    Py_Finalize();
    return 0;
}
#include "Core.hh"

int main() {
    Py::Initialize();
    try {
        Py::Modules::traceback->Call("print", { Py::Str("Hello world") }, nullptr);
    } catch (Py::Exception::Error err) {
        Py::print(err.message);
    }
    std::cout << Py::Modules::traceback << std::endl;
    Py::Module::Import("fsdy3453");
    Py::Exception exc = Py::Exception::Catch();
    std::cout << exc.ToStr() << std::endl;
}
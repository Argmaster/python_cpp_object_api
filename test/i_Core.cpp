#include "Core.hh"

int main() {
    Py::Initialize();
    try {
        Py::Modules.traceback->Call("print", { Py::Str("Hello world") }, nullptr);
    } catch (Py::Exception::Error err) {
        Py::print(err.message);
    }
}
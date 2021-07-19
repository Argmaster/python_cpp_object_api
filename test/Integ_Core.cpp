#include "Core.hh"

int main() {
    Py::Initialize();
    try {
        Py::Modules::traceback->Call("print", { Py::Str("Hello world") }, nullptr);
    } catch (Py::Exception::Error err) {
        Py::print(err);
    }
    std::cout << Py::Modules::traceback << std::endl;
    Py::Module::Import("fsdy3453");
    Py::Exception exc = Py::Exception::Catch();
    try {
        Py::print(Py::Modules::json->GetAttr("sigature"));
    } catch (Py::Exception::Error err) {
        Py::print(err);
    }
    Py::print(Py::Modules::inspect->GetDict());
    auto sigature_func = Py::Modules::inspect->GetAttr("signature").As<Py::Function>();
    std::cout << sigature_func.Signature() << std::endl;
}
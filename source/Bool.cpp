#include "Bool.hh"


bool operator > (bool first, Py::Bool second) { return first > bool(second); }
bool operator >= (bool first, Py::Bool second) { return first >= bool(second); }
bool operator == (bool first, Py::Bool second) { return first == bool(second); }
bool operator != (bool first, Py::Bool second) { return first != bool(second); }
bool operator < (bool first, Py::Bool second) { return first < bool(second); }
bool operator <= (bool first, Py::Bool second) { return first <= bool(second); }
bool operator > (Py::Bool  first, bool second) { return bool(first) > second; }
bool operator >= (Py::Bool  first, bool second) { return bool(first) >= second; }
bool operator == (Py::Bool  first, bool second) { return bool(first) == second; }
bool operator != (Py::Bool  first, bool second) { return bool(first) != second; }
bool operator < (Py::Bool  first, bool second) { return bool(first) < second; }
bool operator <= (Py::Bool  first, bool second) { return bool(first) <= second; }
#include "Str.hh"
#include <assert.h>

void test_1()
{
    {
        Py::Str str("Ala");
        assert(str.RefC() == 1);
        assert(str.IsStr() == 1);
    }
    {
        auto str = Py::Str::FromFormat("Some num: %i and %lu", 1, 2);
        assert(str.AsUTF8() == "Some num: 1 and 2");
        __LOG(str)
    }
}
void test_2()
{
    auto str = Py::Str("Ala");
    auto bytes = str.Encode("utf-8");
    assert(str == "Ala");
    auto str_2 = Py::Str::Decode("some encoded source", "ascii");
    auto bytes_2 = str_2.Encode("ascii");
    assert(str_2.AsUTF8() == std::string("some encoded source"));
    assert(str_2.AsUTF8() == bytes_2.AsString());
}
void test_3()
{
    auto str = Py::Str("The quick brown fox \n jumps over the lazy dog");
    {
        auto words = str.Split(" ");
        assert(words.Length() == 10);
    }
    {
        auto words = str.Splitlines();
        assert(words.Length() == 2);
    }
    {
        auto words = Py::Str("Go hell").Split(" ");
        auto joined = Py::Str(" to ").Join(words);
        assert(joined == "Go to hell");
    }
    {
        assert(Py::Str("The quick brown fox jumps over the lazy dog").Match("The quick"));
        assert(Py::Str("The quick brown fox jumps over the lazy dog").Match("lazy dog", 1));
    }
    {
        assert(Py::Str("The quick brown fox jumps over the lazy dog").Find("The quick") == 0);
        assert(Py::Str("The quick brown fox jumps over the lazy dog").Find("lazy dog", -1) == 35);
        assert(Py::Str("The quick brown fox jumps over the lazy dog").GetItem(Py::Long(35)) == "l");
    }
    {
        assert(Py::Str("The quick brown fox jumps over the lazy dog").Count("a") == 1);
    }
    {
        assert(Py::Str("The quick brown fox jumps over the lazy dog").Replace("quick", "slow").Length() == 42);
    }
    {
        assert(Py::Str("One, %i guns\nLay %s your arms\n").CFormat({ Py::Long(21), Py::Str("down") }) == "One, 21 guns\nLay down your arms\n");
        assert((Py::Str("One, %i guns\nLay %s your arms\n") % Py::Tuple({ Py::Long(21), Py::Str("down") })) == "One, 21 guns\nLay down your arms\n");
    }
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
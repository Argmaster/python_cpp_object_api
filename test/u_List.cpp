#include "List.hh"
#include <assert.h>

void from_pointer_construct()
{
    auto list = Py::New<Py::List>( PyList_New( 0 ) );
    assert( list.RefC() == 1 );
    assert( list.IsNotNull() );
    assert( list.IsSequence() );
    assert( list.IsList() );
    assert( list.Length() == 0 );
    assert( list.ToStr().AsUTF8() == "[]" );
    assert( list.RefC() == 1 );
}
void from_initializer_list_construct()
{
    Py::List list( { Py::Long( 44356 ), Py::Str( "Hello World" ) } );
    assert( list.RefC() == 1 );
    assert( list.IsNotNull() );
    assert( list.IsSequence() );
    assert( list.IsList() );
    assert( list.Length() == 2 );
    assert( list.ToStr().AsUTF8() == "[44356, 'Hello World']" );
    assert( list.RefC() == 1 );
}
void from_size_only_construct()
{
    {
        Py::List list( 0LL );
        assert( list.RefC() == 1 );
        assert( list.IsNotNull() );
        assert( list.IsSequence() );
        assert( list.IsList() );
        assert( list.Length() == 0 );
        assert( list.ToStr().AsUTF8() == "[]" );
        assert( list.RefC() == 1 );
    }
    {
        Py::List list( 2LL );
        assert( list.RefC() == 1 );
        assert( list.IsNotNull() );
        assert( list.IsSequence() );
        assert( list.IsList() );
        assert( list.Length() == 2 );
        assert( list.ToStr().AsUTF8() == "[<NULL>, <NULL>]" );
        assert( list.RefC() == 1 );
    }
}
void method_get_item()
{
    Py::List list( {
        Py::Str( "Example" ),
        Py::Str( "Hello World" ),
        Py::Str( "List" ) } );
    assert( list.GetItem( 0 ).IsNotNull() );
    assert( list.GetItem( 0 ).IsStr() );
    assert( list.GetItem( 0 ).As<Py::Str>().AsUTF8() == "Example" );
    assert( list.GetItem( 2 ).IsNotNull() );
    assert( list.GetItem( 2 ).IsStr() );
    assert( list.GetItem( 2 ).As<Py::Str>().AsUTF8() == "List" );
    assert( list[1].IsNotNull() );
    assert( list[1].IsStr() );
    assert( list[1].As<Py::Str>().AsUTF8() == "Hello World" );
    assert( list.RefC() == 1 );
}
void method_set_item()
{
    Py::List list( 3 );
    list.SetItem( 0, Py::Str( "Example" ) );
    list.SetItem( 1, Py::Str( "Hello World" ) );
    list.SetItem( 2, Py::Str( "List" ) );
    assert( list.GetItem( 0 ).IsNotNull() );
    assert( list.GetItem( 0 ).IsStr() );
    assert( list.GetItem( 0 ).As<Py::Str>().AsUTF8() == "Example" );
    assert( list.GetItem( 1 ).IsNotNull() );
    assert( list.GetItem( 1 ).IsStr() );
    assert( list.GetItem( 1 ).As<Py::Str>().AsUTF8() == "Hello World" );
    assert( list.GetItem( 2 ).IsNotNull() );
    assert( list.GetItem( 2 ).IsStr() );
    assert( list.GetItem( 2 ).As<Py::Str>().AsUTF8() == "List" );
    assert( list.RefC() == 1 );
}
void method_get_slice()
{
    Py::List list( {
        Py::Long( 0LL ),
        Py::Long( 1 ),
        Py::Long( 2 ),
        Py::Long( 3 ),
        Py::Long( 4 ),
        Py::Long( 5 ),
        Py::Long( 6 ),
        Py::Long( 7 ),
        Py::Long( 8 ),
        Py::Long( 9 ),
        Py::Long( 10 )
                   } );
    assert( list.GetSlice( 2, 6 ) == Py::List( {
        Py::Long( 2 ),
        Py::Long( 3 ),
        Py::Long( 4 ),
        Py::Long( 5 )
                                               } )
    );
    assert( list.RefC() == 1 );
}
void method_set_slice()
{
    Py::List list( {
        Py::Long( 0LL ),
        Py::Long( 1 ),
        Py::Long( 2 ),
        Py::Long( 3 ),
        Py::Long( 4 ),
        Py::Long( 5 ),
        Py::Long( 6 ),
        Py::Long( 7 ),
        Py::Long( 8 ),
        Py::Long( 9 ),
        Py::Long( 10 )
                   } );
    auto new_value = Py::List( {
        Py::Long( 99 ),
        Py::Long( 99 ),
        Py::Long( 99 ),
        Py::Long( 99 )
                               } );
    assert( new_value.RefC() == 1 );
    assert( list.SetSlice( 2, 6, new_value ) == 0
    );
    assert( new_value.RefC() == 1 );
    assert(
        list.GetItem( 2 ).As<Py::Int>().AsLongLong() == 99 ||
        list.GetItem( 3 ).As<Py::Int>().AsLongLong() == 99 ||
        list.GetItem( 4 ).As<Py::Int>().AsLongLong() == 99 ||
        list.GetItem( 5 ).As<Py::Int>().AsLongLong() == 99
    );
    assert( list.RefC() == 1 );
}
void method_append()
{
    Py::List list( {} );
    Py::Int value_0( 34343 );
    assert( list.Append( value_0 ) == 0 );
    assert( value_0.RefC() == 2 );
    assert( list.Length() == 1 );
    assert( list[0].As<Py::Int>() == value_0 );
    assert( value_0.RefC() == 2 );
    assert( list.Append( list ) == 0 );
    assert( list.ToStr().AsUTF8() == "[34343, [...]]" );
}
void method_insert()
{
    Py::List list( {} );
    Py::Int value_0( 34343 );
    assert( list.Insert( 0, value_0 ) == 0 );
    assert( value_0.RefC() == 2 );
    assert( list.Length() == 1 );
    assert( list[0].As<Py::Int>() == value_0 );
    for (int i = 0; i < 10; i++) {
        list.Append( Py::Long( i ) );
    }
    assert( list.Insert( 5, value_0 ) == 0 );
    assert( value_0.RefC() == 3 );
    assert( list[5].As<Py::Int>() == value_0 );
}
void method_sort()
{
    Py::List list( {} );
    for (int i = 10; i >= 0; i--) {
        list.Append( Py::Int( i ) );
    }
    assert( list.Sort().IsNotNull() );
    Py::List valid_list( {} );
    for (int i = 0; i <= 10; i++) {
        valid_list.Append( Py::Int( i ) );
    }
    assert( list == valid_list );
}
void method_reverse()
{
    Py::List list( {} );
    for (int i = 10; i >= 0; i--) {
        list.Append( Py::Int( i ) );
    }
    assert( list.Reverse().IsNotNull() );
    Py::List valid_list( {} );
    for (int i = 0; i <= 10; i++) {
        valid_list.Append( Py::Int( i ) );
    }
    assert( list == valid_list );
}
void method_totuple()
{
    Py::List list( { Py::Int( 34 ), Py::Int( 55 ), Py::Int( 96 ) } );
    Py::Tuple tuple = list.ToTuple();
    assert( tuple.IsNotNull() );
    assert( tuple.GetItem( 0 ) == Py::Int( 34 ) );
    assert( tuple.GetItem( 1 ) == Py::Int( 55 ) );
    assert( tuple.GetItem( 2 ) == Py::Int( 96 ) );
}
void method_contains()
{
    Py::List list( { Py::Int( 34 ), Py::Int( 55 ), Py::Int( 96 ) } );
    assert( list.Contains( Py::Int( 34 ) ) );
}
void method_count()
{
    Py::List list( {
        Py::Int( 33 ),
        Py::Int( 33 ),
        Py::Int( 1 ),
        Py::Int( 334 ),
        Py::Int( 32 ),
        Py::Int( 76 ),
        Py::Int( 4 ),
                   } );
    assert( list.Count( Py::Int( 33 ) ) == 2 );
    assert( list.Count( Py::Int( 76 ) ) == 1 );
}
void method_index()
{
    Py::List list( {
        Py::Int( 33 ),
        Py::Int( 33 ),
        Py::Int( 1 ),
        Py::Int( 334 ),
        Py::Int( 32 ),
        Py::Int( 76 ),
        Py::Int( 4 ),
                   } );
    assert( list.Index( Py::Int( 33 ) ) == 0 );
    assert( list.Index( Py::Int( 76 ) ) == 5 );
}
int main( int argc, char* argv[], char* env[] )
{
    Py_Initialize();
    auto index = argc > 1 ? atoi( argv[1] ) : -1;
    switch (index) {
        case(1):
            from_pointer_construct();
            break;

        case(2):
            from_initializer_list_construct();
            break;

        case(3):
            from_size_only_construct();
            break;

        case(4):
            method_get_item();
            break;

        case(5):
            method_set_item();
            break;

        case(6):
            method_get_slice();
            break;

        case(7):
            method_set_slice();
            break;

        case(8):
            method_append();
            break;

        case(9):
            method_insert();
            break;

        case(10):
            method_sort();
            break;

        case(11):
            method_reverse();
            break;

        case(12):
            method_totuple();
            break;

        case(13):
            method_contains();
            break;

        case(14):
            method_count();
            break;

        case(15):
            method_index();
            break;

        default:
            from_pointer_construct();
            from_initializer_list_construct();
            from_size_only_construct();
            method_get_item();
            method_set_item();
            method_get_slice();
            method_set_slice();
            method_append();
            method_insert();
            method_sort();
            method_reverse();
            method_totuple();
            method_contains();
            method_count();
            method_index();
            break;
    }
    Py_Finalize();
    Py::print( "Success" );
    return 0;
}
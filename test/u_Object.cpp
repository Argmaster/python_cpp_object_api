#include "Object.hh"
#include <assert.h>


void from_py_object_ptr_construct()
{
    Py::Object obj = Py::New<Py::Object>( PyLong_FromLongLong( 323 ) );
    assert( obj.IsNotNull() );
    assert( obj.IsLong() );
    assert( obj.RefC() == 1 );
}
void copy_n_move_constructor()
{
    Py::Object obj = Py::New<Py::Object>( PyLong_FromLongLong( 323 ) );
    Py::Object obj2 = obj;
    assert( obj.IsNotNull() );
    assert( obj2.IsNotNull() );
    assert( obj.RefC() == 2 );
    assert( obj2.RefC() == 2 );
    Py::Object obj3 = std::move( obj );
    assert( obj.IsNull() );
    assert( obj3.IsNotNull() );
    assert( obj3.IsLong() );
}
void ref_count_altering()
{
    Py::Object obj = Py::New<Py::Object>( PyLong_FromLongLong( 323 ) );
    assert( obj.INCREF() == obj );
    assert( obj.RefC() == 2 );
    assert( obj++ == obj );
    assert( obj.RefC() == 3 );
    assert( obj.DECREF() == obj );
    assert( obj.RefC() == 2 );
    assert( obj-- == obj );
    assert( obj.RefC() == 1 );
}
void type_cast()
{
    Py::Object obj = Py::New<Py::Object>( PyLong_FromLongLong( 323 ) );
    Py::Long obj_long = obj.As<Py::Long>();
    assert( obj_long.RefC() == 2 );
}
void is_checks()
{
    Py::Object obj = Py::New<Py::Object>( PyLong_FromLongLong( 323 ) );
    assert( obj.IsNotNull() );
    assert( obj.IsLong() == true );
    assert( obj.IsFloat() == false );
    assert( obj.IsComplex() == false );
    assert( obj.IsNumber() == true );
    assert( obj.IsBool() == false );
    assert( obj.IsStr() == false );
    assert( obj.IsBytes() == false );
    assert( obj.IsByteArray() == false );
    assert( obj.IsList() == false );
    assert( obj.IsTuple() == false );
    assert( obj.IsSequence() == false );
    assert( obj.IsBuffer() == false );
    assert( obj.IsCallable() == false );
    assert( obj.IsIterator() == false );
    assert( obj.IsDict() == false );
    assert( obj.IsMapping() == false );
    assert( obj.IsSet() == false );
    assert( obj.IsFrozenSet() == false );
    assert( obj.IsModule() == false );
    assert( obj.IsFunction() == false );
    assert( obj.IsCFunction() == false );
    assert( obj.IsType() == false );
    assert( obj.IsNone() == false );
    assert( obj.IsEllipsis() == false );
    assert( obj.IsSlice() == false );
    assert( obj.IsMemoryView() == false );
    assert( obj.IsGenerator() == false );
    assert( obj.IsCapsule() == false );
    assert( obj.IsCoroutine() == false );
    assert( obj.IsInstanceMethod() == false );
    assert( obj.IsMethod() == false );
    assert( obj.GetType().IsSubclass( PyLong_Type ) == 1 );
    assert( obj.GetType().IsSubclass( PyList_Type ) == 0 );
}
void attr_n_item_methods()
{
    Py::Object obj = Py::New<Py::Object>( PyLong_FromLongLong( 323 ) );
    assert( obj.HasAttr( "__str__" ) == true );
    assert( obj.GetAttr( "__str__" ).IsNotNull() );
    Py::Dict dct( { { "key", Py::Str( "value" ) } } );
    assert( dct.GetItem( "key" ).IsNotNull() );
    assert( dct.SetItem( "key1", Py::Long( 345 ) ) == 0 );
    assert( dct.GetItem( "key1" ).IsNotNull() );
    assert( dct.GetItem( "key1" ).IsLong() );
    assert( dct.DelItem( "key1" ) != -1 );
    assert( dct.GetItem( "key1" ).IsNull() );
}
void comaprisons()
{
    Py::Object v9 = Py::New<Py::Object>( PyLong_FromLongLong( 9 ) );
    Py::Object v8 = Py::New<Py::Object>( PyLong_FromLongLong( 8 ) );
    Py::Object v8_2 = Py::New<Py::Object>( PyLong_FromLongLong( 8 ) );
    assert( v8.LessThan( v9 ) );
    assert( v8 < v9 );
    assert( v8.LessEqual( v9 ) );
    assert( v8 <= v9 );
    assert( v8.Equals( v8_2 ) );
    assert( v8 == v8_2 );
    assert( v9.GreaterThan( v8 ) );
    assert( v9 > v8 );
    assert( v9.GreaterEqual( v8 ) );
    assert( v9 >= v8 );
}
void number_ops()
{
    Py::Object value_1 = Py::New<Py::Object>( PyLong_FromLongLong( 7 ) );
    Py::Object value_2 = Py::New<Py::Object>( PyLong_FromLongLong( 3 ) );
    Py::Object value_3 = Py::New<Py::Object>( PyLong_FromLongLong( 4 ) );
    Py::Object value_4 = Py::New<Py::Object>( PyLong_FromLongLong( 2 ) );
    Py::Object value_5 = Py::New<Py::Object>( PyLong_FromLongLong( -232 ) );
    assert( value_1.Add( value_2 ).As<Py::Long>().AsLongLong() == 10 );
    assert( (value_1 + value_2).As<Py::Long>().AsLongLong() == 10 );
    assert( value_1.Sub( value_2 ).As<Py::Long>().AsLongLong() == 4 );
    assert( (value_1 - value_2).As<Py::Long>().AsLongLong() == 4 );
    assert( value_1.Mul( value_2 ).As<Py::Long>().AsLongLong() == 21 );
    assert( (value_1 * value_2).As<Py::Long>().AsLongLong() == 21 );
    assert( value_3.FloorDiv( value_4 ).As<Py::Int>().AsLongLong() == 2 );
    assert( value_3.TrueDiv( value_4 ).As<Py::Float>().AsDouble() == 2.0 );
    assert( (value_3 / value_4).As<Py::Float>().AsDouble() == 2.0 );
    assert( value_1.Neg().As<Py::Int>().AsLongLong() == -7 );
    assert( (-value_1).As<Py::Int>().AsLongLong() == -7 );
    assert( value_1.Pos().As<Py::Int>().AsLongLong() == 7 );
    assert( (+value_1).As<Py::Int>().AsLongLong() == 7 );
    assert( value_5.Abs().As<Py::Int>().AsLongLong() == 232 );
    assert( value_5.Inv().As<Py::Int>().AsLongLong() == 231 );
    assert( (~value_5).As<Py::Int>().AsLongLong() == 231 );
    assert( value_2.LShift( Py::Long( 1 ) ).As<Py::Int>().AsLongLong() == 6 );
    assert( value_2.RShift( Py::Long( 1 ) ).As<Py::Int>().AsLongLong() == 1 );
    assert( value_2.And( value_3 ).As<Py::Int>().AsLongLong() == 0 );
    assert( value_2.Or( value_3 ).As<Py::Int>().AsLongLong() == 7 );
    assert( value_2.Xor( value_3 ).As<Py::Int>().AsLongLong() == 7 );
}
int main( int argc, char* argv[], char* env[] )
{
    Py_Initialize();
    auto index = argc > 1 ? atoi( argv[1] ) : -1;
    switch (index) {
        case(1):
        {
            from_py_object_ptr_construct();
            break;
        }
        case(2):
        {
            copy_n_move_constructor();
            break;
        }
        case(3):
        {
            ref_count_altering();
            break;
        }
        case(4):
        {
            type_cast();
            break;
        }
        case(5):
        {
            is_checks();
            break;
        }
        case(6):
        {
            attr_n_item_methods();
            break;
        }
        case(7):
        {
            comaprisons();
            break;
        }
        case(8):
        {
            number_ops();
            break;
        }
        default:
        {
            from_py_object_ptr_construct();
            copy_n_move_constructor();
            ref_count_altering();
            type_cast();
            is_checks();
            attr_n_item_methods();
            comaprisons();
            number_ops();
            break;
        }
    }
    Py_Finalize();
    Py::print( "Success" );
    return 0;
}
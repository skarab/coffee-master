#include "kernel/meta/meta.h"
#include "kernel/meta/helpers/meta_object_pointer.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::ObjectPointer);
        COFFEE_Attribute(meta::Object *, _Object, MODE_Serializeable | MODE_Editable);
    COFFEE_EndType();

namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ObjectPointer::ObjectPointer() :
        _Object(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ObjectPointer::~ObjectPointer()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ObjectPointer::SetObject(Object * object)
    {
        _Object = object;
    }

    //--------------------------------------------------------------------------------------------//

    Object * ObjectPointer::GetObject()
    {
        return _Object;
    }

}
}

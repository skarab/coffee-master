//------------------------------------------------------------------------------------------------//
/// @file wide/edition/undo/edition_undo_group.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/edition/undo/edition_undo_group.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    UndoGroup::UndoGroup() :
        _Name("Unknown")
    {
    }

    //--------------------------------------------------------------------------------------------//

    UndoGroup::~UndoGroup()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void UndoGroup::Add(UndoObject* object)
    {
        _Objects.AddItem(object);
    }

    //--------------------------------------------------------------------------------------------//

    void UndoGroup::Undo()
    {
        for (int32 object_index=(int32)_Objects.GetSize()-1 ; object_index>=0 ; --object_index)
            _Objects[object_index]->Undo();
    }

    //--------------------------------------------------------------------------------------------//

    void UndoGroup::Redo()
    {
        for (int32 object_index=(int32)_Objects.GetSize()-1 ; object_index>=0 ; --object_index)
            _Objects[object_index]->Redo();
    }

    //--------------------------------------------------------------------------------------------//

    void UndoGroup::Cancel()
    {
        for (int32 object_index=(int32)_Objects.GetSize()-1 ; object_index>=0 ; --object_index)
            _Objects[object_index]->Undo();
        _Objects.Clear();
    }

}
}
//------------------------------------------------------------------------------------------------//

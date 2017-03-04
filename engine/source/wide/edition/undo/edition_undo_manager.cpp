#include "wide/edition/undo/edition_undo_manager.h"
#include "wide/edition/plugin/edition_plugin.h"

namespace coffee
{
namespace edition
{
    //-VARIABLES----------------------------------------------------------------------------------//

    input::Command* UndoManager::UndoCommand = NULL;
    input::Command* UndoManager::RedoCommand = NULL;

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    UndoManager::UndoManager() :
        _CurrentGroup(NULL),
        _ItHasBeenModified(false)
    {
        if (RedoCommand==NULL && input::Module::IsAvailable())
        {
            UndoCommand = COFFEE_New(input::Command, "Undo", "Undo the last command", input::KEY_Control, input::KEY_Z);
            input::System::Get().RegisterCommand(UndoCommand);
            RedoCommand = COFFEE_New(input::Command, "Redo", "Redo the last command", input::KEY_Control, input::KEY_Z, input::KEY_Shift);
            input::System::Get().RegisterCommand(RedoCommand);
        }
    }

    //--------------------------------------------------------------------------------------------//

    UndoManager::~UndoManager()
    {
        Empty();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void UndoManager::SetPlugin(Plugin* plugin)
    {
        _Plugin = plugin;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow< UndoGroup*, true >& UndoManager::GetUndoGroupArray() const
    {
        return _UndoGroupArray;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow< UndoGroup*, true >& UndoManager::GetRedoGroupArray() const
    {
        return _RedoGroupArray;
    }

    //--------------------------------------------------------------------------------------------//

    const UndoGroup& UndoManager::GetLastUndoGroup() const
    {
        return *_UndoGroupArray[_UndoGroupArray.GetSize()-1];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool UndoManager::IsActive() const
    {
        return _CurrentGroup != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool UndoManager::HasUndoGroup() const
    {
        return _UndoGroupArray.GetSize() > 0;
    }

    //--------------------------------------------------------------------------------------------//

    bool UndoManager::HasRedoGroup() const
    {
        return _RedoGroupArray.GetSize() > 0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void UndoManager::Begin()
    {
        COFFEE_Assert(!IsActive(), core::ERROR_CODE_Unexpected, "UndoManager failure");

        _CurrentGroup = COFFEE_New(UndoGroup);
    }

    //--------------------------------------------------------------------------------------------//

    void UndoManager::Accept(basic::String name)
    {
        COFFEE_Assert(IsActive(), core::ERROR_CODE_Unexpected, "UndoManager failure");

        _CurrentGroup->SetName(name);
        _UndoGroupArray.AddItem(_CurrentGroup);
        _RedoGroupArray.Erase();
        _CurrentGroup = NULL;
        _ItHasBeenModified = true;
    }

    //--------------------------------------------------------------------------------------------//

    void UndoManager::Cancel()
    {
        COFFEE_Assert(IsActive(), core::ERROR_CODE_Unexpected, "UndoManager failure");
        _CurrentGroup->Cancel();
        COFFEE_Delete(_CurrentGroup);
        _CurrentGroup = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void UndoManager::Add(UndoObject* object)
    {
        COFFEE_Assert(IsActive(), core::ERROR_CODE_Unexpected, "UndoManager failure");
        _CurrentGroup->Add(object);
    }

    //--------------------------------------------------------------------------------------------//

    void UndoManager::CancelObjects()
    {
        COFFEE_Assert(IsActive(), core::ERROR_CODE_Unexpected, "UndoManager failure");
        _CurrentGroup->Cancel();
    }

    //--------------------------------------------------------------------------------------------//

    void UndoManager::Undo()
    {
        COFFEE_Assert(!IsActive() && HasUndoGroup(), core::ERROR_CODE_Unexpected, "UndoManager failure");

        UndoGroup* group = _UndoGroupArray[_UndoGroupArray.GetSize()-1];
        _UndoGroupArray[_UndoGroupArray.GetSize()-1] = NULL;
        _UndoGroupArray.Remove(_UndoGroupArray.GetSize()-1);
        group->Undo();
        _RedoGroupArray.AddItem(group);
        _ItHasBeenModified = true;
    }

    //--------------------------------------------------------------------------------------------//

    void UndoManager::Redo()
    {
        COFFEE_Assert(!IsActive() && HasRedoGroup(), core::ERROR_CODE_Unexpected, "UndoManager failure");

        UndoGroup* group = _RedoGroupArray[_RedoGroupArray.GetSize()-1];
        _RedoGroupArray[_RedoGroupArray.GetSize()-1] = NULL;
        _RedoGroupArray.Remove(_RedoGroupArray.GetSize()-1);
        group->Redo();
        _UndoGroupArray.AddItem(group);
        _ItHasBeenModified = true;
    }

    //--------------------------------------------------------------------------------------------//
    
    void UndoManager::Empty()
    {
        if (IsActive())
        {
            _CurrentGroup->Cancel();
            COFFEE_Delete(_CurrentGroup);
            _CurrentGroup = NULL;
        }

        _UndoGroupArray.Erase();
        _RedoGroupArray.Erase();
        _ItHasBeenModified = true;
    }

    //--------------------------------------------------------------------------------------------//
    
    void UndoManager::Update()
    {
        if (_ItHasBeenModified)
        {
            _ItHasBeenModified = false;
        }
    }

}
}

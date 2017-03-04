#include "wide/edition/selection/edition_selection_manager.h"
#include "wide/edition/selection/edition_selection_undo.h"
#include "wide/edition/plugin/edition_plugin.h"

namespace coffee
{
namespace edition
{
    //-VARIABLES----------------------------------------------------------------------------------//

    input::Command* SelectionManager::CopyCommand = NULL;
    input::Command* SelectionManager::CutCommand = NULL;
    input::Command* SelectionManager::PasteCommand = NULL;
    input::Command* SelectionManager::DeleteCommand = NULL;
    
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SelectionManager::SelectionManager() :
        _ItHasBeenModified(false)
    {
        if (CopyCommand==NULL && input::Module::IsAvailable())
        {
            CopyCommand = COFFEE_New(input::Command, "Copy", "Copy selected object(s)", input::KEY_Control, input::KEY_C);
            input::System::Get().RegisterCommand(CopyCommand);
            CutCommand = COFFEE_New(input::Command, "Cut", "Cut selected object(s)", input::KEY_Control, input::KEY_X);
            input::System::Get().RegisterCommand(CutCommand);
            PasteCommand = COFFEE_New(input::Command, "Paste", "Paste selected object(s)", input::KEY_Control, input::KEY_V);
            input::System::Get().RegisterCommand(PasteCommand);
            DeleteCommand = COFFEE_New(input::Command, "Delete", "Delete selected object(s)", input::KEY_Delete);
            input::System::Get().RegisterCommand(DeleteCommand);
        }
    }

    //--------------------------------------------------------------------------------------------//

    SelectionManager::~SelectionManager()
    {
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    void SelectionManager::SetPlugin(Plugin* plugin)
    {
        _Plugin = plugin;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 SelectionManager::GetObjectCount() const
    {
        return _ObjectArray.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Object& SelectionManager::GetObject(uint32 index) const
    {
        return *_ObjectArray[index];
    }

    //--------------------------------------------------------------------------------------------//

    meta::Object& SelectionManager::GetObject(uint32 index)
    {
        return *_ObjectArray[index];
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow< meta::Object* >& SelectionManager::GetObjectArray() const
    {
        return _ObjectArray;
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool SelectionManager::IsObjectSelected(meta::Object& object) const
    {
        return _ObjectArray.FindItem(&object)!=NONE;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void SelectionManager::Select(meta::Object& object, bool it_is_selected,
		bool it_has_to_handle_undo, bool it_has_to_accept_undo)
    {
        if (it_has_to_handle_undo)
        {
            if (!_Plugin->GetUndoManager().IsActive())
			    _Plugin->GetUndoManager().Begin();
            _Plugin->GetUndoManager().Add(COFFEE_New(SelectionUndo));

			if (it_has_to_accept_undo)
				_Plugin->GetUndoManager().Accept("Select");
        }

        _ItHasBeenModified = true;

        uint32 index = _ObjectArray.FindItem(&object);

        if (it_is_selected)
        {
            if (index==NONE)
                _ObjectArray.AddItem(&object);
        }
        else
        {
            if (index!=NONE)
                _ObjectArray.Remove(index);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void SelectionManager::Clear(bool it_has_to_handle_undo, bool it_has_to_accept_undo)
    {
        if (it_has_to_handle_undo)
        {
            bool it_has_to_create_chunk(true);

            if (!_Plugin->GetUndoManager().IsActive() && _Plugin->GetUndoManager().HasUndoGroup())
            {
                const UndoGroup& group = _Plugin->GetUndoManager().GetLastUndoGroup();

                if (group.GetName()=="Select"
                    && !static_cast<const SelectionUndo*>(group.GetObjects()[0])->HasObject())
                {
                    it_has_to_create_chunk = false;
                }
            }

            if (it_has_to_create_chunk)
            {
				if (!_Plugin->GetUndoManager().IsActive())
					_Plugin->GetUndoManager().Begin();
                _Plugin->GetUndoManager().Add(COFFEE_New(SelectionUndo));
				if (it_has_to_accept_undo)
					_Plugin->GetUndoManager().Accept("Select");
            }
        }

        _ItHasBeenModified = true;
        _ObjectArray.Erase();
    }

    //--------------------------------------------------------------------------------------------//

    void SelectionManager::Update()
    {
        if (_ItHasBeenModified)
        {
			if (_Plugin->HasActiveControl() && _Plugin->GetActiveControl().IsKindOf<GizmoController>())
				static_cast<GizmoController&>(_Plugin->GetActiveControl()).OnSelectionChanged();
			_ItHasBeenModified = false;
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SelectionManager::_Select(basic::Prow< meta::Object* >& object_array)
    {
        _ObjectArray = object_array;
		_ItHasBeenModified = true;
    }
    
}
}

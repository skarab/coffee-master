//------------------------------------------------------------------------------------------------//
/// @file wide/edition/selection/edition_selection_undo.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/edition/selection/edition_selection_undo.h"
#include "wide/application/application.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SelectionUndo::SelectionUndo()
    {
        COFFEE_Assert(Application::Get().GetControlManager().HasEditionPlugin(),
            core::ERROR_CODE_IncorrectUsage, "Unexpected behavior");
        edition::Plugin& plugin = Application::Get().GetControlManager().GetEditionPlugin();
        _UndoObjectArray = plugin.GetSelectionManager().GetObjectArray();
    }

    //--------------------------------------------------------------------------------------------//

    SelectionUndo::~SelectionUndo()
    {
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool SelectionUndo::HasObject() const
    {
        return _UndoObjectArray.GetSize()>0;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void SelectionUndo::Undo()
    {
        _RedoObjectArray = Application::Get().GetControlManager().GetEditionPlugin().GetSelectionManager().GetObjectArray();
        Application::Get().GetControlManager().GetEditionPlugin().GetSelectionManager()._Select(_UndoObjectArray);
    }

    //--------------------------------------------------------------------------------------------//

    void SelectionUndo::Redo()
    {
        Application::Get().GetControlManager().GetEditionPlugin().GetSelectionManager()._Select(_RedoObjectArray);
    }
    
}
}
//------------------------------------------------------------------------------------------------//

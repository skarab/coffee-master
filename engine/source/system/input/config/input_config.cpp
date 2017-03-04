//------------------------------------------------------------------------------------------------//
/// @file system/input/config/input_config.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "system/input/config/input_config.h"
#include "wide/edition/selection/edition_selection_manager.h"
#include "wide/edition/undo/edition_undo_manager.h"
#include "wide/application/application.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(input::Config);
        COFFEE_Ancestor(shell::ModuleConfig);
        COFFEE_AttributeCustom(< input::Command * >, _Shortcuts, COFFEE_New(meta::ParamArrayCombo, meta::MODE_Serializeable | meta::MODE_Editable, basic::String("Name")));
    COFFEE_EndType();

namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Config::Config()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Config::~Config()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Config::SetDefaults()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Config::Apply()
    {
        basic::Prow<Command*> commands;
        _RetrieveCommands(commands);
        _RemoveUnusedCommands(commands);
        _ApplyConfig(commands);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Config::_RetrieveCommands(basic::Prow<Command*>& command_array)
    {
        // Currently its NULL when there is no edition plugin (ex: unittest / player projects)
        if (edition::SelectionManager::CopyCommand!=NULL)
        {
            command_array.AddItem(edition::SelectionManager::CopyCommand);
            command_array.AddItem(edition::SelectionManager::CutCommand);
            command_array.AddItem(edition::SelectionManager::PasteCommand);
            command_array.AddItem(edition::SelectionManager::DeleteCommand);
            command_array.AddItem(edition::UndoManager::UndoCommand);
            command_array.AddItem(edition::UndoManager::RedoCommand);
        }

        _RetrieveControlCommands(command_array,
            Application::Get().GetControlManager());
    }

    //--------------------------------------------------------------------------------------------//

    void Config::_RetrieveControlCommands(basic::Prow<Command*>& command_array,
        ApplicationControl& control)
    {
        uint32 index;
        if (control.HasCommand())
            command_array.AddItem(&control.GetCommand());
        for (index=0 ; index<control.GetCommandArray().GetSize() ; ++index)
            command_array.AddItem(control.GetCommandArray()[index]);
        for (index=0 ; index<control.GetChildCount() ; ++index)
        {
            _RetrieveControlCommands(command_array,
                static_cast<ApplicationControl&>(control.GetChild(index)));
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Config::_RemoveUnusedCommands(const basic::Prow<Command*>& command_array)
    {
        for (int32 index=0 ; index<(int32)_Shortcuts.GetSize() ; ++index)
        {
            bool it_has_to_remove=true;
            for (uint32 i=0 ; i<command_array.GetSize() ; ++i)
            {
                if (_Shortcuts[(int32)index]->GetName()==command_array[i]->GetName())
                {
                    it_has_to_remove = false;
                    break;
                }
            }
            if (it_has_to_remove)
            {
                _Shortcuts.Remove((uint32)index);
                --index;
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Config::_ApplyConfig(basic::Prow<Command*>& command_array)
    {
        for (uint32 index=0 ; index<command_array.GetSize() ; ++index)
        {
            bool it_has_to_add=true;
            for (uint32 i=0 ; i<_Shortcuts.GetSize() ; ++i)
            {
                if (command_array[index]->GetName()==_Shortcuts[i]->GetName())
                {
                    _Shortcuts[i]->SetDescription(command_array[index]->GetDescription());
                    *command_array[index] = *_Shortcuts[i];
                    it_has_to_add=false;
                    break;
                }
            }
            if (it_has_to_add)
            {
                _Shortcuts.AddItem(COFFEE_New(input::Command, *command_array[index]));
            }
        }
    }

}
}
//------------------------------------------------------------------------------------------------//

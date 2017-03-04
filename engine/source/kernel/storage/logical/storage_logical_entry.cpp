#include "kernel/storage/logical/storage_logical_entry.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    LogicalEntry::LogicalEntry()
    {
    }

    //--------------------------------------------------------------------------------------------//

    LogicalEntry::~LogicalEntry()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void LogicalEntry::SetName(const basic::String & name)
    {
        _Name = name;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String & LogicalEntry::GetName() const
    {
        return _Name;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    LogicalEntry* LogicalEntry::FindChild(const basic::String & child_name)
    {
        for (uint32 i=0 ; i<GetChildCount() ; ++i)
        {
            if (GetChild(i).GetName()==child_name)
                return &GetChild(i);
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void LogicalEntry::List(basic::Prow<LogicalEntry*>& entry_array, bool it_has_to_list_folders,
        bool it_has_to_list_files, bool it_is_recursive)
    {
        for (uint32 i=0 ; i<GetChildCount() ; ++i)
        {
            LogicalEntry* entry = &GetChild(i);
            if (entry->IsFile())
            {
                if (it_has_to_list_files)
                    entry_array.AddItem(entry);
            }
            else
            {
                if (it_has_to_list_folders)
                    entry_array.AddItem(entry);
                if (it_is_recursive)
                    entry->List(entry_array, it_has_to_list_folders, it_has_to_list_files, it_is_recursive);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    Path LogicalEntry::GetPath() const
    {
        basic::String path("/");
        const LogicalEntry * entry = this;
        path += _Name;
        while (entry->HasParent() && entry->GetParent().HasParent())
        {
            entry = &entry->GetParent();
            path = basic::String("/") + entry->GetName() + path;
        }
        return Path(path);
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalEntry::IsFile() const
    {
        return false;
    }

}
}

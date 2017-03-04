#include "kernel/storage/physical/storage_physical_path.h"
#include "kernel/storage/physical/storage_physical_system.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(storage::PhysicalPath);
        COFFEE_Ancestor(basic::String);
    COFFEE_EndType();

namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PhysicalPath::PhysicalPath()
    {
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath::PhysicalPath(const char* path)
    {
        Set(basic::String(path));
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath::PhysicalPath(const basic::String& path)
    {
        Set(path);
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath::PhysicalPath(const PhysicalPath& path)
    {
        Set(path);
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath::~PhysicalPath()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    PhysicalPath& PhysicalPath::operator=(const char* path)
    {
        Set(path);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath& PhysicalPath::operator =(const basic::String& path)
    {
        Set(path);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath& PhysicalPath::operator =(const PhysicalPath& path)
    {
        Set(path);
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool PhysicalPath::HasPath() const
    {
        return FindLast('/')!=0;
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath PhysicalPath::GetPath() const
    {
        PhysicalPath path(*this);
        uint32 index = FindLast('/');
        if (index==0 || index==NONE)
            return "";
        return path.GetLeft(index);
    }
        
    //--------------------------------------------------------------------------------------------//

    bool PhysicalPath::IsFilePath() const
    {
        return IsContaining('.');
    }

    //--------------------------------------------------------------------------------------------//

    basic::String PhysicalPath::GetFileName() const
    {
        uint32 index = FindLast('/');
        if (index==NONE)
            return "";
        return GetRight(GetLength()-index-1);
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::String PhysicalPath::GetFileExtension() const
    {
        uint32 index = FindLast('.');
        if (index==NONE)
            return "";
        return GetRight(GetLength()-index-1);
    }

    //--------------------------------------------------------------------------------------------//

    basic::String PhysicalPath::GetFileNameWithoutExtension() const
    {
        basic::String filename(GetFileName());
        uint32 index = filename.FindLast('.');
        if (index!=NONE)
            return filename.GetLeft(index);
        return "";
    }

    //--------------------------------------------------------------------------------------------//

    basic::Text PhysicalPath::GetHierarchy() const
    {
        basic::Text entry_list;
        int32 entry_index(NONE);
        basic::String entry_name;
        while(GetNextWord(entry_name, entry_index, '/'))
            entry_list.AddLine(entry_name);
        return entry_list;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PhysicalPath::Set(const basic::String& path)
    {
        basic::String::operator =(path);

        for (uint32 index=0 ; index<GetLength() ; ++index)
        {
            if (GetBuffer()[index]=='\\')
                GetBuffer()[index] = '/';
        }

        if (GetLength()>0 && GetBuffer()[GetLength()-1]=='/')
            basic::String::operator --();

        if (GetLength()>0 && GetBuffer()[0]=='/')
            basic::String::Set(GetRight(GetLength()-1).GetBuffer());

        if (GetLength()>0 && !IsContaining(":"))
            basic::String::operator=(PhysicalSystem::Get().GetRootFolder()+"/"+*this);
    }

}
}

#include "kernel/storage/logical/storage_path.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(storage::Path);
        COFFEE_Ancestor(basic::String);
    COFFEE_EndType();

namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Path::Path()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Path::Path(const char* path)
    {
        Set(basic::String(path));
    }

    //--------------------------------------------------------------------------------------------//

    Path::Path(const basic::String& path)
    {
        Set(path);
    }

    //--------------------------------------------------------------------------------------------//

    Path::Path(const Path& path)
    {
        Set(path);
    }

    //--------------------------------------------------------------------------------------------//

    Path::~Path()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Path& Path::operator =(const char* path)
    {
        Set(basic::String(path));
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Path& Path::operator =(const basic::String& path)
    {
        Set(path);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Path& Path::operator =(const Path& path)
    {
        Set(path);
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Path::HasPath() const
    {
        return FindLast('/')!=NONE;
    }

    //--------------------------------------------------------------------------------------------//

    Path Path::GetPath() const
    {
        Path path(*this);
        uint32 index = FindLast('/');
        if (index==0 || index==NONE)
            return "";
        return path.GetLeft(index);
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Path::GetName() const
    {
        uint32 index = FindLast('/');
        if (index!=NONE)
            return GetRight(GetLength()-index-1);
        return basic::String();
    }

    //--------------------------------------------------------------------------------------------//

    bool Path::IsFilePath() const
    {
        return IsContaining('.');
    }

    //--------------------------------------------------------------------------------------------//
    
    basic::String Path::GetFileName() const
    {
        basic::String filename(GetName());
        if (!filename.IsContaining('.'))
            filename.SetEmpty();
        return filename;
    }
        
    //--------------------------------------------------------------------------------------------//

    basic::String Path::GetFileExtension() const
    {
        uint32 index = FindLast('.');
        if (index!=NONE)
            return GetRight(GetLength()-index-1);
        return basic::String();
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Path::GetFileNameWithoutExtension() const
    {
        basic::String filename(GetFileName());
        uint32 index = filename.FindLast('.');
        if (index!=NONE)
            return filename.GetLeft(index);
        return "";
    }
        
    //--------------------------------------------------------------------------------------------//

    basic::Text Path::GetHierarchy() const
    {
        basic::Text entry_list;
        int32 entry_index(NONE);
        basic::String entry_name;
        while (GetNextWord(entry_name, entry_index, '/'))
            entry_list.AddLine(entry_name);
        return entry_list;
    }

    //--------------------------------------------------------------------------------------------//

    storage::Path Path::GetHeadFilePath(const basic::String& extension) const
    {
        storage::Path head = "";
        basic::Text items = GetHierarchy();
        for (uint32 i=1 ; i<items.GetLineCount() ; ++i)
        {
            if ((extension=='*' && items[i].IsContaining('.'))
                || (extension!='*' && items[i].IsSuffixed(basic::String(".")+extension)))
            {
                for (uint32 j=1 ; j<i+1 ; ++j)
                {
                    head += "/";
                    head += items[j];
                }
                break;
            }
        }
        return head;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Path::SetFileExtension(const basic::String& extension)
    {
        this->operator -=(GetFileExtension().GetLength());
        this->operator +=(extension);
    }

    //--------------------------------------------------------------------------------------------//

    void Path::Set(const basic::String& path)
    {
        basic::String::operator =(path);
        uint32 character_index;

        for (character_index=0 ; character_index<GetLength() ; ++character_index )
        {
            if (GetBuffer()[character_index]=='\\')
                GetBuffer()[character_index] = '/';
        }

        if ((GetLength()>0) && (GetBuffer()[GetLength()-1]=='/'))
            basic::String::operator --();

        if ((GetLength()>0) && (GetBuffer()[0]!='/'))
            basic::String::Set((basic::String("/") + *this).GetBuffer());
    }

}
}

#ifdef COFFEE_OS_WINDOWS

//-DEFINES----------------------------------------------------------------------------------------//

#define COFFEE_STORAGE_PHYSICAL_SYSTEM_Invalid               (void *)((long *) - 1)
#define COFFEE_STORAGE_PHYSICAL_SYSTEM_InvalidAttributes     ((DWORD)-1)
#define COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute       0x00000010
#define COFFEE_STORAGE_PHYSICAL_SYSTEM_ReadOnlyAttribute     0x00000001

namespace coffee
{
namespace storage
{
    //-QUERIES------------------------------------------------------------------------------------//

    bool PhysicalSystem::IsFolder(const PhysicalPath& path) const
    {
        DWORD attributes = GetFileAttributes(path.GetBuffer());
        if (attributes==COFFEE_STORAGE_PHYSICAL_SYSTEM_InvalidAttributes)
            return false;
        return (attributes&COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute)>0;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::IsFile(const PhysicalPath& path) const
    {
        DWORD attributes = GetFileAttributes(path.GetBuffer());
        if (attributes==COFFEE_STORAGE_PHYSICAL_SYSTEM_InvalidAttributes)
            return false;
        return (attributes&COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute)==0;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::IsReadOnly(const PhysicalPath& path) const
    {
        DWORD attributes = GetFileAttributes(path.GetBuffer());
        return (attributes&COFFEE_STORAGE_PHYSICAL_SYSTEM_ReadOnlyAttribute)>0;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::ListDrives(basic::Prow<PhysicalPath*, true> & drives) const
    {
        for (uint32 index=0 ; index<20 ; ++index)
        {
            basic::String name("A:\\");
            name.GetBuffer()[0] += 20-index;
            DWORD type = GetDriveType(name.GetBuffer());
            if (type!=DRIVE_UNKNOWN && type!=DRIVE_NO_ROOT_DIR)
                drives.AddItem(COFFEE_New(PhysicalPath, name));
        }
        return !drives.IsEmpty();
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::List(basic::Prow<PhysicalPath *, true> & pathes,
        const PhysicalPath& path, bool it_wants_folders, bool it_wants_files,
        basic::String extension, bool it_is_recursive) const
    {
        WIN32_FIND_DATA file_ptr;
        void* find_ptr = FindFirstFile((path+'/'+extension).GetBuffer(), &file_ptr);
        if (find_ptr==COFFEE_STORAGE_PHYSICAL_SYSTEM_Invalid)
            return false;

        do
        {
            basic::String name(file_ptr.cFileName);
            if (file_ptr.dwFileAttributes&COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute
                && !name.IsContaining('.'))
            {
                if (it_wants_folders)
                {
                    PhysicalPath folder_path(path+'/'+file_ptr.cFileName);
                    pathes.AddItem(COFFEE_New(PhysicalPath, folder_path));
                    if (it_is_recursive)
                    {
                        List(pathes, folder_path, it_wants_folders,
                            it_wants_files, extension, it_is_recursive);
                    }
                }
            }
            else if (it_wants_files && name!="." && name!="..")
            {
                pathes.AddItem(COFFEE_New(PhysicalPath, path+'/'+file_ptr.cFileName));
            }
        }
        while (FindNextFile(find_ptr, &file_ptr));
        FindClose(find_ptr);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::CreateFile(const PhysicalPath& path, bool it_replaces) const
    {
        if (IsFile(path) && !it_replaces)
            return false;
        FILE* file = fopen(path.GetBuffer(), "wb");
        if (file!=NULL)
            fclose(file);
        return IsFile(path);
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::RemoveFile(const PhysicalPath& path) const
    {
        if (!IsFile(path))
            return false;
        DeleteFile(path.GetBuffer());
        return !IsFile(path);
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::SetFileData(const PhysicalPath& path, const Data& data) const
    {
        bool result(false);
        FILE* file = fopen(path.GetBuffer(), "wb");
        if (file!=NULL)
        {
            if (fwrite(data.GetBuffer(), sizeof(char), data.GetSize(), file)==data.GetSize())
                result = true;
            fclose(file);
        }
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    Data* PhysicalSystem::GetFileData(const PhysicalPath& path) const
    {
        Data* data(NULL);
        WIN32_FIND_DATA file_ptr;
        void* find_ptr = FindFirstFile(path.GetBuffer(), &file_ptr);
        if (find_ptr!=COFFEE_STORAGE_PHYSICAL_SYSTEM_Invalid)
        {
            data = COFFEE_New(Data);
            data->Resize(file_ptr.nFileSizeLow);
            FindClose(find_ptr);

            FILE* file = fopen(path.GetBuffer(), "rb");
            if (file==NULL)
            {
                COFFEE_Delete(data);
                return NULL;
            }
            if (fread(data->GetBuffer(), sizeof(char), data->GetSize(), file)!=data->GetSize())
            {
                COFFEE_Delete(data);
                data = NULL;
            }
            fclose(file);
        }
        return data;
    }

    //--------------------------------------------------------------------------------------------//

    FileAccess* PhysicalSystem::GetFileAccess(const PhysicalPath& path) const
    {
        if (!IsFile(path))
            return NULL;
        return COFFEE_New(FileAccess, path);
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::CopyFile(const PhysicalPath& from, const PhysicalPath& to,
        bool it_replaces) const
    {
        if (IsFile(to) && (!it_replaces || !::DeleteFile(to.GetBuffer())))
            return false;
        if (to.HasPath() && !IsFolder(to.GetPath()) && !CreateFolder(to.GetPath()))
            return false;
        return ::CopyFile(from.GetBuffer(), to.GetBuffer(), true)!=FALSE;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::MoveFile(const PhysicalPath& from, const PhysicalPath& to, bool it_replaces) const
    {
        return CopyFile(from, to, it_replaces)
            && RemoveFile(from);
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::CreateFolder(const PhysicalPath& path) const
    {
        basic::Text folders = path.GetHierarchy();
        basic::String folder;
        for (uint32 i=0 ; i<folders.GetLineCount() ; ++i)
        {
            folder += folders[i];
            folder += '/';
            if (!IsFolder(folder))
            {
                if (::CreateDirectory(folder.GetBuffer(), NULL)==FALSE
                    || !IsFolder(folder))
                {
                    return false;
                }
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool _RemoveFolder(const PhysicalPath& path)
    {
        WIN32_FIND_DATA file_ptr;
        void* find_ptr = FindFirstFile((path+"/*.*").GetBuffer(), &file_ptr);
        if (find_ptr==COFFEE_STORAGE_PHYSICAL_SYSTEM_Invalid)
            return false;

        do
        {
            basic::String name(file_ptr.cFileName);
            if (name!="." && name!="..")
            {
                if (file_ptr.dwFileAttributes&COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute)
                {
                    if (!_RemoveFolder(path+'/'+file_ptr.cFileName))
                    {
                        FindClose(find_ptr);
                        return false;
                    }
                }
                else if (::DeleteFile((path+'/'+file_ptr.cFileName).GetBuffer())==FALSE)
                {
                    FindClose(find_ptr);
                    return false;
                }
            }
        }
        while (FindNextFile(find_ptr, &file_ptr));
        FindClose(find_ptr);
        return ::RemoveDirectory(path.GetBuffer())!=FALSE;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::RemoveFolder(const PhysicalPath& path) const
    {
        if (!_RemoveFolder(path))
            return false;

        // account for filesystem refresh time...
        Sleep(60);

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool _CopyFolder(const PhysicalPath& from, const PhysicalPath& to, bool (*filter)(meta::Object* user, const PhysicalPath& path), meta::Object* user)
    {
        WIN32_FIND_DATA file_ptr;
        void* find_ptr = FindFirstFile((from+"/*.*").GetBuffer(), &file_ptr);
        if (find_ptr==COFFEE_STORAGE_PHYSICAL_SYSTEM_Invalid)
            return false;
        
        do
        {
            basic::String name(file_ptr.cFileName);
            if (name!="." && name!="..")
            {
                if (filter!=NULL && !filter(user, from+"/"+name))
                    continue;

                if (file_ptr.dwFileAttributes&COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute)
                {
                    if ((!storage::PhysicalSystem::Get().IsFolder(to+"/"+name)
                        && ::CreateDirectory((to+"/"+name).GetBuffer(), NULL)==FALSE)
                        || !_CopyFolder(from+"/"+name, to+"/"+name, filter, user))
                    {
                        FindClose(find_ptr);
                        return false;
                    }
                }
                else
                {
                    if (::CopyFile((from+"/"+name).GetBuffer(), (to+"/"+name).GetBuffer(), FALSE)==FALSE)
                    {
                        FindClose(find_ptr);
                        return false;
                    }
                }
            }
        }
        while (FindNextFile(find_ptr, &file_ptr));
        FindClose(find_ptr);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::CopyFolder(const PhysicalPath& from, const PhysicalPath& to,
        bool it_replaces, bool (*filter)(meta::Object* user, const PhysicalPath& path), meta::Object* user) const
    {
        if (it_replaces && IsFolder(to) && !RemoveFolder(to))
            return false;
        if (!CreateFolder(to))
            return false;
        return _CopyFolder(from, to, filter, user);
    }

    //--------------------------------------------------------------------------------------------//

    bool PhysicalSystem::MoveFolder(const PhysicalPath& from, const PhysicalPath& to, bool it_replaces) const
    {
        return CopyFolder(from, to, it_replaces)
            && RemoveFolder(from);
    }
    
}
}

#undef COFFEE_STORAGE_PHYSICAL_SYSTEM_Invalid
#undef COFFEE_STORAGE_PHYSICAL_SYSTEM_InvalidAttributes
#undef COFFEE_STORAGE_PHYSICAL_SYSTEM_FolderAttribute
#undef COFFEE_STORAGE_PHYSICAL_SYSTEM_ReadOnlyAttribute

#endif

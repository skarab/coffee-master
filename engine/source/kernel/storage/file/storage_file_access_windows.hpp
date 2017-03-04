#ifdef COFFEE_OS_WINDOWS

#define COFFEE_STORAGE_FILE_ACCESS_Invalid  (void *)((long *) - 1)

namespace coffee
{
namespace storage
{
    //-QUERIES------------------------------------------------------------------------------------//

    basic::Date FileAccess::GetLastWriteDate() const
    {
        basic::Date last_write_date;
        WIN32_FIND_DATA file_ptr;
        void* find_ptr;
        find_ptr = FindFirstFile(_Path.GetBuffer(), &file_ptr);
        if (find_ptr!=COFFEE_STORAGE_FILE_ACCESS_Invalid)
        {
            SYSTEMTIME system_date;
            FileTimeToSystemTime(&file_ptr.ftLastWriteTime, &system_date);
            core::Platform::Get().ConvertDate(last_write_date, system_date);
            FindClose(find_ptr);
        }
        return last_write_date;
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    bool FileAccess::_Platform_Open()
    {
        if (_Mode==MODE_Output)
        {
            _Size = 0;

            if ((_File=fopen(_Path.GetBuffer(), "wb"))==0)
                return false;
        }
        else
        {
            WIN32_FIND_DATA file_ptr;
            void* find_ptr;

            find_ptr = FindFirstFile(_Path.GetBuffer(), &file_ptr);

            if (find_ptr==COFFEE_STORAGE_FILE_ACCESS_Invalid)
            {
                if (_Mode==MODE_Input)
                    return false;
            }
            else
            {
                FindClose(find_ptr);
                _Size = file_ptr.nFileSizeLow;
            }

            if (_Mode==MODE_Input)
            {
                if ((_File=fopen(_Path.GetBuffer(), "rb"))==0)
                    return false;
            }
            else
            {
                if ((_File=fopen(_Path.GetBuffer(), "rb+"))==0)
                    return false;
            }
        }

        SetOffset(0);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::_Platform_Close()
    {
        fclose(_File);
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::_Platform_SetOffset(ulong offset)
    {
        fseek(_File, offset, SEEK_SET);
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::_Platform_Read(char * buffer, ulong size)
    {
        fread(buffer, sizeof(char), size, _File);
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::_Platform_Write(const char * buffer, ulong size)
    {
        fwrite(buffer, sizeof(char), size, _File);
    }

}
}

#undef COFFEE_STORAGE_FILE_ACCESS_Invalid

#endif

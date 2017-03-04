#ifdef COFFEE_OS_WINDOWS

namespace coffee
{
namespace plugins
{
    //-ACCESSORS------------------------------------------------------------------------------//

    HINSTANCE Object::GetDllInstance()
    {
        return static_cast<Object&>(GetResource())._DllInstance;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Object::_Initialize()
    {
        _DllInstance = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void Object::_Finalize()
    {
        COFFEE_Assert(_DllInstance==NULL, core::ERROR_CODE_Unexpected,
            "Library shouldnt be loaded at this point");
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::_LoadLibrary()
    {
        COFFEE_Assert(_DllInstance==NULL, core::ERROR_CODE_Unexpected,
            "Library shouldnt be loaded at this point");

        basic::String path = storage::System::Get().GetPhysicalFilePath(GetLibraryPath()).GetPath();
        path += "/";
        path += GetLibraryPath().GetFileNameWithoutExtension() + ".dll";
        _DllInstance = LoadLibrary(path.GetBuffer());
        return _DllInstance!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::_UnloadLibrary()
    {
        if (_DllInstance!=NULL && FreeLibrary(_DllInstance)!=FALSE)
        {
            _DllInstance = NULL;
            return true;
        }
        return true;
    }

}
}
#endif

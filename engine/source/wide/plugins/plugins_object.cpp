#include "wide/plugins/plugins_object.h"
#include "wide/plugins/plugins_object_windows.hpp"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(plugins, Object, "Plugin", "plugin", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_Attribute(storage::Path, _LibraryPath, meta::MODE_Serializeable);
        COFFEE_ResourceProperty(plugins::Library*, _Library, meta::MODE_Editable, 0);
    COFFEE_EndResource();

namespace plugins
{
    plugins::Library* Object::_Loading = NULL;

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Object::Object() :
        _Library(NULL)
    {
        _Initialize();
    }

    //--------------------------------------------------------------------------------------------//

    Object::~Object()
    {
        _Finalize();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Library& Object::GetLibrary() const
    {
        return *_Library.Get();
    }

    //--------------------------------------------------------------------------------------------//

    Library& Object::GrabLibrary()
    {
        return *_Library.Grab();
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool Object::IsReady() const
    {
        return _Library.Get()!=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Object::Initialize()
    {
        if (!IsInstantiated())
        {
            COFFEE_Assert(_Loading==NULL, core::ERROR_CODE_Unexpected, "Bad plugin loading");
            bool result = _LoadLibrary();
            if (result)
            {
                COFFEE_Assert(_Loading!=NULL, core::ERROR_CODE_Unexpected, "Bad plugin loading");
                _Library.Set(_Loading);
            }
            _Loading = NULL;
            return result;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::Finalize()
    {
        if (!IsInstantiated())
        {
            _Library.Get()->_Finalize();
            COFFEE_Delete(_Library.Get());
            _Library.Set(NULL);
            bool result = _UnloadLibrary();
            return result;
        }
        return true;
    }

}
}

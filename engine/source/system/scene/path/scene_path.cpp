#include "system/scene/path/scene_path.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::Path);
        COFFEE_Ancestor(storage::Path);
        COFFEE_Attribute(storage::Path, _ScenePath, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Path::Path(storage::Path path) :
        storage::Path(path)
    {
        _Update();
    }

    //--------------------------------------------------------------------------------------------//

    Path::~Path()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Path& Path::operator =(const Path& path)
    {
        Set(path);
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Path::IsValid() const
    {
        return _ScenePath.GetLength()>0;
    }

    //--------------------------------------------------------------------------------------------//

    storage::Path Path::GetNodePath() const
    {
        if (!IsValid())
            return "";
        return GetRight(GetLength()-_ScenePath.GetLength());
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Path::_Update()
    {
        _ScenePath = GetHeadFilePath("scene");
    }

}
}

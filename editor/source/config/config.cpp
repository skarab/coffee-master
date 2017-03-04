#include "config/config.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(Config);
        COFFEE_Attribute(ui::Skin, _Skin, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

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
        _Skin = resource::Manager::Get().Load(COFFEE_GUI_DefaultSkin);
    }

    //--------------------------------------------------------------------------------------------//

    void Config::Apply()
    {
        ui::WindowManager::Get().SetSkin(_Skin);
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Config::OnPropertyModified(const void* prop)
    {
        if (prop==&_Skin)
        {
            if (!_Skin.GetFilePath().IsPrefixed("/coffee/"))        
                _Skin = resource::Manager::Get().Load(COFFEE_GUI_DefaultSkin);
            Apply();
        }
    }

}

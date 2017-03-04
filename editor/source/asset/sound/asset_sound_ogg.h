#ifndef _EDITOR_ASSET_SOUND_OGG_H_
#define _EDITOR_ASSET_SOUND_OGG_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// OGG sound importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SoundOGG : public Importer
    {
        COFFEE_Type(SoundOGG);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SoundOGG();
        ~SoundOGG();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIs3D;
        bool _ItIsLooping;
        real _Pitch;
        real _Gain;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SoundOGG);
}
}
#endif

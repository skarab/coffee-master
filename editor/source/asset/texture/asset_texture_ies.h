#ifndef _EDITOR_ASSET_TEXTURE_IES_H_
#define _EDITOR_ASSET_TEXTURE_IES_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// IES light/texture importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API TextureIES : public Importer
    {
        COFFEE_Type(TextureIES);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TextureIES();
        ~TextureIES();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        real _ComputeIESValue(const basic::Vector2& position) const;
        bool _FindNearestVerticalAngleIndex(uint32& first_index, uint32& second_index, real angle) const;

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Exponent;
        real _Scale;
        real _Distance;
        basic::String _LampType;
        basic::String _Manufacturer;
        basic::String _Measurement;
        basic::Array<int32> _VerticalAngles;
        int32 _SymmetryType;
        basic::Array<int32> _CandelaValues;
        int32 _MinimumCandela;
        int32 _MaximumCandela;        
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, TextureIES);
}
}
#endif

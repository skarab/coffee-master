#ifndef _COFFEE_GRAPHICS_TEXTURE_H_
#define _COFFEE_GRAPHICS_TEXTURE_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "system/graphics/texture/graphics_texture_parameter.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Texture base class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Texture : public resource::Object
    {
        COFFEE_Resource(Texture);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Texture();
        virtual ~Texture();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetParameters(uint32 parameters);
        void EnableParameter(const TEXTURE_PARAMETER& parameter, bool it_has_to_enable);
        bool IsParameterEnabled(const TEXTURE_PARAMETER& parameter) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual bool Initialize();
        virtual bool Finalize();
        virtual void Bind(uint32 multi_texture_index = 0);
        virtual void UnBind(uint32 multi_texture_index = 0);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< uint32 > _Parameters;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Texture);
}
}
#endif

#ifndef _COFFEE_GRAPHICS_MODULE_H_
#define _COFFEE_GRAPHICS_MODULE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/device/graphics_device.h"
#include "system/graphics/frame/graphics_frame.h"
#include "system/graphics/geometric/graphics_geometric_renderer.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/font/graphics_font.h"
#include "system/graphics/texture/graphics_texture.h"
#include "system/graphics/texture/2d/graphics_texture_2d.h"
#include "system/graphics/texture/array/graphics_texture_array.h"
#include "system/graphics/texture/3d/graphics_texture_3d.h"
#include "system/graphics/shader/graphics_shader.h"
#include "system/graphics/material/graphics_material.h"
#include "system/graphics/mesh/graphics_mesh.h"
#include "system/graphics/sky/graphics_sky.h"
#include "system/graphics/component/graphics_components.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics Module
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Module : public shell::Module
    {
        COFFEE_Type(Module);
        COFFEE_DeclareModuleSingleton(Module);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Module();
        ~Module();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Device* _Device;
        Renderer* _Renderer;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Module);
}
}
#endif

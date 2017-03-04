#include "system/graphics/gatherer/graphics_chunk.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Chunk::Chunk(ComponentMesh* component, uint32 surface_index) :
        _Component(component),
        _SurfaceIndex(surface_index)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Chunk::~Chunk()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void Chunk::Render(Viewport& viewport)
    {
        COFFEE_GRAPHICS_Debug();        
        if (_Component->GetMesh().IsAvailable())
            _Component->Render(_SurfaceIndex, viewport);
        COFFEE_GRAPHICS_Debug();
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::RenderShadows(Viewport& viewport, Material& material)
    {
        if (_Component->GetMesh().IsAvailable())
            _Component->RenderShadows(_SurfaceIndex, viewport, material);
    }

}
}

#ifndef _COFFEE_GRAPHICS_CHUNK_H_
#define _COFFEE_GRAPHICS_CHUNK_H_

#include "coffee_includes.h"
#include "system/graphics/component/mesh/graphics_component_mesh.h"

namespace coffee
{
namespace graphics
{
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Gathered chunk
    ///
    /// Single surface pointing to a mesh, it has a single material as well.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Chunk
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Chunk(ComponentMesh* component=NULL, uint32 surface_index=NONE);
        ~Chunk();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Render(Viewport& viewport);
        void RenderShadows(Viewport& viewport, Material& material);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ComponentMesh* _Component;
        uint32 _SurfaceIndex;
    };
}
}
#endif

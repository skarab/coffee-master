#ifndef _COFFEE_GRAPHICS_GATHERER_H_
#define _COFFEE_GRAPHICS_GATHERER_H_

#include "coffee_includes.h"
#include "system/graphics/gatherer/graphics_chunk.h"
#include "system/graphics/gatherer/graphics_light.h"

namespace coffee
{
namespace graphics
{
    class ComponentCamera;
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Gatherer
    ///
    /// It gathers all graphics elements, needed by the frame pass system:
    /// . visible opaque chunks, sorted front to back
    /// . visible transparent chunks, sorted back to front
    /// . visible lights, containing shadow chunks
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Gatherer : public meta::Object
    {
        COFFEE_Type(Gatherer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Gatherer();
        ~Gatherer();

        //-ACCESSORS------------------------------------------------------------------------------//

        basic::Prow<Chunk*, true>& GetOpaqueChunks() { return _OpaqueChunks; }
        basic::Prow<Chunk*, true>& GetTransparentChunks() { return _TransparentChunks; }
        basic::Prow<Light*, true>& GetLights() { return _Lights; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Clear();
        void Update(scene::Node& root, const ComponentCamera& camera, const Viewport& viewport);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Gather(scene::Node& node, const ComponentCamera& camera,
            basic::Prow<ComponentLight*>& lights, basic::Prow<ComponentMesh*>& meshes,
            basic::Rope<real>& distances);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<Chunk*, true> _OpaqueChunks;
        basic::Prow<Chunk*, true> _TransparentChunks;
        basic::Prow<Light*, true> _Lights;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Gatherer);
}
}
#endif

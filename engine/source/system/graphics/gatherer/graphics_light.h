#ifndef _COFFEE_GRAPHICS_LIGHT_H_
#define _COFFEE_GRAPHICS_LIGHT_H_

#include "coffee_includes.h"
#include "system/graphics/gatherer/graphics_chunk.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
namespace graphics
{
    class ComponentCamera;
    class ComponentLight;

    //--------------------------------------------------------------------------------------------//
    /// Gathered light
    ///
    /// Pointing to a light component, it contains the list of shadowed chunks.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Light
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Light();
        ~Light();

        //-ACCESSORS------------------------------------------------------------------------------//

        const ComponentLight& GetComponent() const { return *_Component; }
        ComponentLight& GetComponent() { return *_Component; }
        const basic::Prow<Chunk*, true>& GetChunks() const { return _Chunks; }
        basic::Prow<Chunk*, true>& GetChunks() { return _Chunks; }
        const basic::Rope<bool>& GetCappedShadows() const { return _CappedShadows; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Gather(ComponentLight& component, scene::Node& root, const ComponentCamera& camera);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Gather(scene::Node& node, const basic::Sphere& sphere,
            const basic::Sphere& camera_sphere, const ComponentCamera& camera);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ComponentLight* _Component;
        basic::Prow<Chunk*, true> _Chunks;
        basic::Rope<bool> _CappedShadows;
    };
}
}
#endif

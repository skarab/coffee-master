#include "system/graphics/gatherer/graphics_gatherer.h"
#include "system/graphics/component/camera/graphics_component_camera.h"
#include "system/graphics/component/light/graphics_component_light.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::Gatherer);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Gatherer::Gatherer()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Gatherer::~Gatherer()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Gatherer::Clear()
    {
        _OpaqueChunks.Clear();
        _TransparentChunks.Clear();
        _Lights.Clear();
    }

    //--------------------------------------------------------------------------------------------//

    void Gatherer::Update(scene::Node& root, const ComponentCamera& camera, const Viewport& viewport)
    {
        basic::Prow<ComponentLight*> lights;
        basic::Prow<ComponentMesh*> meshes;
        basic::Rope<real> distances;
        _Gather(root, camera, lights, meshes, distances);

        for (uint32 i=0 ; i<meshes.GetSize() ; ++i)
        {
            if (meshes[i]->GetMesh().IsAvailable())
            for (uint32 j=0 ; j<meshes[i]->GetMesh().GetSurfaceCount() ; ++j)
            {
                if (meshes[i]->GetMesh().GetMaterial(j).IsAvailable())
                {
                    Chunk* chunk = COFFEE_New(Chunk, meshes[i], j);
                    if (meshes[i]->GetMesh().GetMaterial(j).GetRenderState().IsBlendingEnabled())
                    {
                        _TransparentChunks.AddItem(chunk, 0);
                    }
                    else
                    {
                        _OpaqueChunks.AddItem(chunk);
                    }
                }
            }
        }

        for (uint32 i=0 ; i<lights.GetSize() ; ++i)
        {
            Light* light = COFFEE_New(Light);
            light->Gather(*lights[i], root, camera);
            _Lights.AddItem(light);
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Gatherer::_Gather(scene::Node& node, const ComponentCamera& camera,
        basic::Prow<ComponentLight*>& lights, basic::Prow<ComponentMesh*>& meshes,
        basic::Rope<real>& distances)
    {
        if (node.IsRunning() && node.HasTransform() && node.HasBounding()
            && node.GetTransform().IsRunning() && node.GetBounding().IsRunning())
        {
            basic::Vector3 camera_translation = camera.GetNode().GetTransform().GetMatrix(
                scene::TRS_Local, scene::TRS_World).GetTranslation();
            basic::Vector3 node_translation = node.GetTransform().GetMatrix(
                scene::TRS_Local, scene::TRS_World).GetTranslation();
            real distance = camera_translation.GetDistance(node_translation);

            bool it_is_visible = distance-node.GetBounding().GetSphere().Radius<camera.GetFarClip()
                && camera.GetFrustum().IsSphereOverlapping(
                    node.GetBounding().GetSphere()*node.GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World))
                && camera.GetFrustum().IsBoxOverlapping(
                    node.GetBounding().GetBox()*node.GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
        
            if (it_is_visible)
            {
                if (node.HasGraphics() && node.GetGraphics().IsRunning())
                {
                    if (node.GetGraphics().IsKindOf<ComponentLight>())
                    {
                        ComponentLight* component = static_cast<ComponentLight*>(&node.GetGraphics());
                        if (component->GetMaterial().IsAvailable())
                            lights.AddItem(component);
                    }
                    else if (node.GetGraphics().IsKindOf<ComponentMesh>())
                    {
                        ComponentMesh* component = static_cast<ComponentMesh*>(&node.GetGraphics());
                        if (component->GetMesh().IsAvailable())
                        {
                            uint32 index = NONE;
                            for (uint32 i=0 ; i<distances.GetSize() ; ++i)
                            {
                                if (distance<distances[i])
                                {
                                    index = i;
                                    break;
                                }
                            }
                            meshes.AddItem(component, index);
                            distances.AddItem(distance, index);
                        }
                    }
                }

                for (uint32 i=0 ; i<node.GetChildCount() ; ++i)
                    _Gather(node.GetChild(i), camera, lights, meshes, distances);
            }
        }
    }
        
}
}

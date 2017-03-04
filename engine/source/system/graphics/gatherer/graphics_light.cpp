#include "system/graphics/gatherer/graphics_light.h"
#include "system/graphics/component/camera/graphics_component_camera.h"
#include "system/graphics/component/light/graphics_component_light.h"
#include "system/graphics/component/light/directional/graphics_component_light_directional.h"

namespace coffee
{
namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Light::Light() :
        _Component(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Light::~Light()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Light::Gather(ComponentLight& component, scene::Node& root, const ComponentCamera& camera)
    {
        _Component = &component;

        if (camera.IsFlagEnabled(COMPONENT_FLAG_CastShadows)
            && component.IsFlagEnabled(COMPONENT_FLAG_CastShadows))
        {
            basic::Sphere sphere = _Component->GetNode().GetBounding().GetSphere()
                *_Component->GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
            basic::Sphere camera_sphere(camera.GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation(),
                2.0f);

            _Gather(root, sphere, camera_sphere, camera);
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Light::_Gather(scene::Node& node, const basic::Sphere& sphere,
        const basic::Sphere& camera_sphere, const ComponentCamera& camera)
    {
        if (node.IsRunning() && node.HasTransform() && node.HasBounding()
            && node.GetTransform().IsRunning() && node.GetBounding().IsRunning())
        {
            basic::Sphere node_sphere(node.GetBounding().GetSphere()
                *node.GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
            
            if (_Component->IsA<ComponentLightDirectional>()
                || sphere.IsOverlapping(node_sphere))
            {
                if (node.HasGraphics() && node.GetGraphics().IsRunning())
                {
                    if (node.GetGraphics().IsKindOf<ComponentMesh>())
                    {
                        ComponentMesh* component = static_cast<ComponentMesh*>(&node.GetGraphics());
                        if (component->IsFlagEnabled(COMPONENT_FLAG_CastShadows)
                            && component->GetMesh().IsAvailable())
                        {
                            // Check if camera is inside the shadow volume
                            bool requires_capped_shadows = false;
                            if (_Component->IsA<ComponentLightDirectional>()
                                || sphere.IsOverlapping(camera_sphere))
                            {
                                requires_capped_shadows = true;
                                if (!camera_sphere.IsOverlapping(node_sphere))
                                {
                                    if (_Component->IsA<ComponentLightDirectional>())
                                    {
                                        basic::Vector3 direction = _Component->GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetZAxis();
                                        if (!direction.IsZero())
                                        {
                                            direction.Normalize();
                                            basic::Line3 line(node_sphere.Center, direction);
                                            real distance = line.ComputeDistanceFromPoint(camera_sphere.Center);
                                            requires_capped_shadows = distance<=node_sphere.Radius+camera_sphere.Radius;
                                        }
                                    }
                                    else
                                    {
                                        basic::Vector3 direction = node_sphere.Center-sphere.Center;
                                        basic::Vector3 camera_direction = camera_sphere.Center-sphere.Center;
                                        if (!direction.IsZero() && !camera_direction.IsZero())
                                        {
                                            direction.Normalize();
                                            camera_direction.Normalize();
                                            if (direction!=basic::Vector3::YAxis)
                                            {
                                                basic::Vector3 dir = direction.GetOrthogonal(basic::Vector3::YAxis);
                                                if (!dir.IsZero())
                                                {
                                                    dir.Normalize();
                                                    basic::Vector3 maximum_direction = node_sphere.Center+dir
                                                        *(node_sphere.Radius+camera_sphere.Radius)-sphere.Center;
                                                    if (!maximum_direction.IsZero())
                                                    {
                                                        maximum_direction.Normalize();
                                                        requires_capped_shadows = direction.GetDotProduct(camera_direction)
                                                            >=direction.GetDotProduct(maximum_direction);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            Mesh& mesh = component->GetMesh();
                            for (uint32 i=0 ; i<mesh.GetSurfaceCount() ; ++i)
                            {
                                if (mesh.GetMaterial(i).IsAvailable()
                                    && !mesh.GetMaterial(i).GetRenderState().IsBlendingEnabled())
                                {
                                    Chunk* chunk = COFFEE_New(Chunk, component, i);
                                    _Chunks.AddItem(chunk);
                                    _CappedShadows.AddItem(requires_capped_shadows);
                                }
                            }
                        }
                    }
                }

                for (uint32 i=0 ; i<node.GetChildCount() ; ++i)
                    _Gather(node.GetChild(i), sphere, camera_sphere, camera);
            }
        }
    }

}
}

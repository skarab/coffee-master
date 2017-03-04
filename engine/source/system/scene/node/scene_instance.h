#ifndef _COFFEE_SCENE_INSTANCE_H_
#define _COFFEE_SCENE_INSTANCE_H_

#include "coffee_includes.h"
#include "system/scene/scene_resource.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Scene node instantiating a scene object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Instance : public Node
    {
        COFFEE_Type(Instance);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Instance();
        Instance(const storage::Path& resource_path);
        ~Instance();

        //-ACCESSORS------------------------------------------------------------------------------//

        const scene::Resource& GetSource() const { return _Source; }
        scene::Resource& GetSource() { return _Source; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Destroy();
        void FixedUpdate(const basic::Time& time_step);
        
        void PreSerialize(storage::MODE mode);
        void PostSerialize(storage::MODE mode);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _StripNotInstantiables(Node& node);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        scene::Resource _Source;
        resource::Handler<scene::Resource> _Handler;    
        Node* _Temp;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Instance);
}
}
#endif

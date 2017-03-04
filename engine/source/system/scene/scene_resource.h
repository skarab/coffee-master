#ifndef _COFFEE_SCENE_RESOURCE_H_
#define _COFFEE_SCENE_RESOURCE_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
namespace scene
{
    class Instance;

    //--------------------------------------------------------------------------------------------//
    /// Scene resource
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Resource : public resource::Object
    {
        friend class Instance;

        COFFEE_Resource(Resource);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Resource();
        ~Resource();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Node& GetRoot() const;
        Node& GetRoot();
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        void ConstructInstance();
        bool InitializeInstance();
        bool FinalizeInstance();
        void PreSerialize(storage::MODE mode);
        void PostSerialize(storage::MODE mode);

        Node* FindNode(const Path& path);

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property<Node*> _Root;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Resource);
}
}
#endif

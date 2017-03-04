#include "wide/edition/plugin/edition_plugin_detach_node_undo.h"

namespace coffee
{
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PluginDetachNodeUndo::PluginDetachNodeUndo(scene::Node* node) :
        _Node(node),
		_Parent(NULL)
    {
		if (_Node->HasParent())
        {
            _Transform = _Node->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
			_Parent = static_cast<scene::Node*>(&_Node->GetParent());
        }
    }

    //--------------------------------------------------------------------------------------------//

    PluginDetachNodeUndo::~PluginDetachNodeUndo()
    {
		if (!_Node->HasParent())
			_Node->Destroy();
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void PluginDetachNodeUndo::Undo()
    {
        if (_Parent!=NULL)
		{
			_Parent->Attach(*_Node);
            basic::Matrix local_to_parent(_Transform
                * _Node->GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Parent));
            _Node->GetTransform().SetPosition(
                local_to_parent.GetTranslation(),
                local_to_parent.GetRotation(),
                local_to_parent.GetScale());
		}
    }

    //--------------------------------------------------------------------------------------------//

    void PluginDetachNodeUndo::Redo()
    {
		if (_Parent!=NULL)
		{
            _Transform = _Node->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
			_Node->Detach();
		}
    }

}
}

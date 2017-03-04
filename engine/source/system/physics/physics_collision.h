#ifndef _COFFEE_PHYSICS_COLLISION_H_
#define _COFFEE_PHYSICS_COLLISION_H_

#include "coffee_includes.h"

namespace coffee
{
namespace physics
{
    class RigidBody;

    //--------------------------------------------------------------------------------------------//
    /// Hold collision information, passed to rigid bodies and whole components
    //--------------------------------------------------------------------------------------------//
    struct COFFEE_API Collision
    {
        //-OPERATIONS-----------------------------------------------------------------------------//

        bool operator==(const Collision& collision) const
        {
            return (NodeBody==collision.NodeBody && OtherBody==collision.OtherBody)
                || (NodeBody==collision.OtherBody && OtherBody==collision.NodeBody);
        }

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        RigidBody* NodeBody;    ///< the rigid body of the current node
        RigidBody* OtherBody;   ///< the other rigid body which is colliding
    
        bool ItIsFirstTime;
        bool ItIsLastTime;

        uint32 Stamp;

        // TODO: Add contact informations on Collision
    };
}
}
#endif

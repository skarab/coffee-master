#ifndef _COFFEE_PHYSICS_CHARACTER_H_
#define _COFFEE_PHYSICS_CHARACTER_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Character gives access to move, strafe, jump behaviors
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Character : public RigidBody
    {
        COFFEE_Component(Character, "Character", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Character();
        ~Character();

        //-ACCESSORS------------------------------------------------------------------------------//

        void Set(real move, real strafe, real jump);

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnFixedUpdate(const basic::Time& time_step);
        void OnPropertyModified(const void* prop);
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Initialize(physics::Scene& scene);
        void _Finalize(physics::Scene& scene);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Height;
        real _Radius;
        real _Move;
        real _Strafe;
        real _Jump;

        // temp: no more needed in Newton 3.x

    private:
            
        class CharacterBody
        {
        public:
            CharacterBody() :
                _Controller(NULL),
                m_body(NULL)
            {
            }

            ~CharacterBody()
            {
            }

            void Init(dFloat mass, dFloat x, dFloat z, dFloat height, dFloat max_step, const dMatrix& local_frame)
            {
                _Shape = NewtonCreateCapsule(m_world, x, height, 0, NULL);

                dVector origin;
        	    dVector inertia;
                NewtonConvexCollisionCalculateInertialMatrix(_Shape, &inertia[0], &origin[0]);	
    	
                dFloat Ixx;
	            dFloat Iyy;
	            dFloat Izz;
        	    Ixx = mass * inertia[0];
	            Iyy = mass * inertia[1];
	            Izz = mass * inertia[2];

                basic::Matrix matrix;
                
                m_body = NewtonCreateBody (m_world, _Shape, matrix.GetData());

                NewtonReleaseCollision (m_world, _Shape);

	            // set the correct center of gravity for this body
	            NewtonBodySetCentreOfMass (m_body, &origin[0]);

	            // set the mass matrix
	            NewtonBodySetMassMatrix (m_body, mass, Ixx, Iyy, Izz);

	            _Controller = new CustomPlayerController(local_frame, m_body, max_step, 1.0f / 64.0f); 
            }

            void SetRestrainingDistance(dFloat distance)
            {
            }

            bool IsJumping() const { return _Controller->IsJumping(); }

            void SetPlayerVelocity(dFloat move, dFloat strafe, dFloat jump, dFloat angle, const dVector& gravity, dFloat time_step)
            {
                 _Controller->SetVelocity (move*3.0f, strafe*3.0f, jump, angle);
            }

            void PostUpdate(dFloat time_step, int thread_index)
            {
                // It's done automatically from Newton.
                //_Controller->SubmitConstraints(time_step, thread_index);
            }

            NewtonWorld* m_world;
            NewtonBody* m_body;
            NewtonCollision* _Shape;
            CustomPlayerController* _Controller;
        };

        CharacterBody* _CharacterBody;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Character);
}
}
#endif

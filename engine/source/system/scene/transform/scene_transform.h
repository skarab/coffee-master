#ifndef _COFFEE_SCENE_TRANSFORM_H_
#define _COFFEE_SCENE_TRANSFORM_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"
#include "system/scene/transform/scene_trs.h"

namespace coffee
{
namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Component handling the node transform matrix
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Transform : public scene::Component
    {
        COFFEE_Component(Transform, "Transform", "Scene/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Transform();
        ~Transform();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetTranslation(const basic::Vector3& translation);
        const basic::Vector3& GetTranslation() const { return _Translation; }
        void SetRotation(const basic::Quaternion& rotation);
        const basic::Quaternion& GetRotation() const { return _Rotation; }
        void SetScale(const basic::Vector3& scale);
        const basic::Vector3& GetScale() const { return _Scale; }
        const basic::Matrix& GetMatrix(TRS from, TRS to) const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsUpToDate() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetPosition(const basic::Vector3& translation, const basic::Quaternion& rotation, const basic::Vector3& scale);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
        void OnFixedUpdate(const basic::Time& time_step);
        void OnPropertyModified(const void* prop);        
        void OnPhysicsTransform(const basic::Vector3& translation,
            const basic::Quaternion& rotation, bool it_has_to_apply_rotation);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _UpdateMatrices();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector3 _Translation;
        basic::Quaternion _Rotation;
        basic::Vector3 _Scale;
        basic::Matrix _LocalToParentMatrix;
        basic::Matrix _ParentToLocalMatrix;
        basic::Matrix _LocalToWorldMatrix;
        basic::Matrix _WorldToLocalMatrix;
        TRS_FLAG _TranslationFlag;
        TRS_FLAG _RotationFlag;
        TRS_FLAG _ScaleFlag;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Transform);
}
}
#endif

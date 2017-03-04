#include "system/scene/transform/scene_transform.h"
#include "system/scene/node/scene_node.h"
#include "wide/edition/edition.h"
#include "wide/application/application.h"
#include "system/physics/physics_component.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::Transform);
        COFFEE_Ancestor(scene::Component);
        COFFEE_Attribute(basic::Vector3, _Translation, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(basic::Quaternion, _Rotation, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(basic::Vector3, _Scale, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Transform::Transform() :
        _Scale(basic::Vector3::One),
        _TranslationFlag(TRS_FLAG_None),
        _RotationFlag(TRS_FLAG_None),
        _ScaleFlag(TRS_FLAG_None)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Transform::~Transform()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Transform::SetTranslation(const basic::Vector3& translation)
    {
        if (translation!=_Translation)
        {
            _Translation = translation;
            _TranslationFlag = TRS_FLAG_User;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Transform::SetRotation(const basic::Quaternion& rotation)
    {
        if (rotation!=_Rotation)
        {
            _Rotation = rotation;
            _RotationFlag = TRS_FLAG_User;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Transform::SetScale(const basic::Vector3& scale)
    {
        if (scale!=_Scale)
        {
            _Scale = scale;
            ClampMinimum(_Scale.X, 0.02f);
            ClampMinimum(_Scale.Y, 0.02f);
            ClampMinimum(_Scale.Z, 0.02f);
            _ScaleFlag = TRS_FLAG_User;
        }
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Matrix& Transform::GetMatrix(TRS from, TRS to) const
    {
        if (from==TRS_Local)
        {
            if (to==TRS_Parent) return _LocalToParentMatrix;
            if (to==TRS_World)  return _LocalToWorldMatrix;
        }
        else if (from==TRS_Parent)
        {
            if (to==TRS_Local) return _ParentToLocalMatrix;
            if (to==TRS_World)
            {
                if (!GetNode().HasParent() || !GetNode().GetParent().HasTransform())
                    return basic::Matrix::Identity;
                return GetNode().GetParent().GetTransform().GetMatrix(TRS_Local, TRS_World);
            }
        }
        else if (to==TRS_Local)
        {
            return _WorldToLocalMatrix;
        }
        else if (to==TRS_Parent)
        {
            if (!GetNode().HasParent() || !GetNode().GetParent().HasTransform())
                return basic::Matrix::Identity;
            return GetNode().GetParent().GetTransform().GetMatrix(TRS_World, TRS_Local);
        }
        return basic::Matrix::Identity;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Transform::IsUpToDate() const
    {
        return _TranslationFlag==TRS_FLAG_None
            && _RotationFlag==TRS_FLAG_None 
            && _ScaleFlag==TRS_FLAG_None;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Transform::SetPosition(const basic::Vector3& translation,
        const basic::Quaternion& rotation, const basic::Vector3& scale)
    {
        SetTranslation(translation);
        SetRotation(rotation);
        SetScale(scale);
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Transform::OnStart()
    {
        _TranslationFlag = TRS_FLAG_User;
        _RotationFlag = TRS_FLAG_User;
        _ScaleFlag = TRS_FLAG_User;
        _UpdateMatrices();
    }

    //--------------------------------------------------------------------------------------------//

    void Transform::OnStop()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Transform::OnUpdate(const basic::Time& time_step)
    {
        OnFixedUpdate(time_step);
    }
        
    //--------------------------------------------------------------------------------------------//

    void Transform::OnFixedUpdate(const basic::Time& time_step)
    {
        TRS_FLAG translation_flag = _TranslationFlag;
        TRS_FLAG rotation_flag = _RotationFlag;
        TRS_FLAG scale_flag = _ScaleFlag;            

        if (_UpdateMatrices())
        {
            for (uint32 child_index=0 ; child_index<GetNode().GetChildCount() ; ++child_index)
            {
                if (GetNode().GetChild(child_index).HasTransform())
                {
                    GetNode().GetChild(child_index).GetTransform()._TranslationFlag = TRS_FLAG_User;
                    GetNode().GetChild(child_index).GetTransform()._RotationFlag = TRS_FLAG_User;
                    GetNode().GetChild(child_index).GetTransform()._ScaleFlag = TRS_FLAG_User;
                }
            }

            if (GetNode().HasParent() && GetNode().GetParent().HasBounding())
                GetNode().GetParent().GetBounding().OnTransform();
        
            if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
            {
                bool it_has_to_update(false);

                if (translation_flag==TRS_FLAG_User || scale_flag==TRS_FLAG_User)
                    it_has_to_update = true;

                if (GetNode().GetRigidBody().IsHandlingRotation() && rotation_flag==TRS_FLAG_User)
                    it_has_to_update = true;

                if (it_has_to_update)
                    GetNode().GetRigidBody().OnTransform();
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Transform::OnPropertyModified(const void* prop)
    {
        if (prop==&_Translation)
            _TranslationFlag = TRS_FLAG_User;
        else if (prop==&_Rotation)
            _RotationFlag = TRS_FLAG_User;
        else if (prop==&_Scale)
            _ScaleFlag = TRS_FLAG_User;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Transform::OnPhysicsTransform(const basic::Vector3& translation,
        const basic::Quaternion& rotation, bool it_has_to_apply_rotation)
    {
        if (_TranslationFlag==TRS_FLAG_None)
        {
            _Translation = translation;
            _TranslationFlag = TRS_FLAG_Physics;
        }

        if (it_has_to_apply_rotation && _RotationFlag==TRS_FLAG_None)
        {
            _Rotation = rotation;
            _RotationFlag = TRS_FLAG_Physics;
        }        
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    bool Transform::_UpdateMatrices()
    {
        if (!IsUpToDate())
        {
            if (GetNode().HasParent() && GetNode().GetParent().HasTransform()
                && !GetNode().GetParent().GetTransform().IsUpToDate())
            {
                return false;
            }

            _LocalToParentMatrix.Set(_Translation, _Rotation, _Scale);
            _ParentToLocalMatrix.SetInversed(_LocalToParentMatrix);
            _LocalToWorldMatrix = _LocalToParentMatrix;

            if (GetNode().HasParent() && GetNode().GetParent().HasTransform())
            {
                _LocalToWorldMatrix *= GetNode().GetParent().GetTransform().GetMatrix(TRS_Local, TRS_World);
                _WorldToLocalMatrix.SetInversed(_LocalToWorldMatrix);
            }
            else
            {
                _WorldToLocalMatrix = _ParentToLocalMatrix;
            }
            
            _TranslationFlag = TRS_FLAG_None;
            _RotationFlag = TRS_FLAG_None;
            _ScaleFlag = TRS_FLAG_None;
            return true;
        }
        return false;
    }


}
}

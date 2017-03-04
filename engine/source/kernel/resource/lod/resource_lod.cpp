//------------------------------------------------------------------------------------------------//
/// @file kernel/resource/lod/resource_lod.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/resource/lod/resource_lod.h"
#include "kernel/resource/resource_object.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::LOD);
        COFFEE_Attribute(resource::LOD_STATE, _State, meta::MODE_Editable);
        COFFEE_Attribute(resource::Object *, _Data, meta::MODE_Editable);
        COFFEE_Attribute(resource::LODParameters *, _Parameters, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace resource
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    LOD::LOD() :
        _State(LOD_STATE_Unused),
        _Data(NULL),
        _Parameters(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    LOD::~LOD()
    {
        if (HasData())
            COFFEE_Delete(_Data);

        if (HasParameters())
            COFFEE_Delete(_Parameters);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void LOD::SetState(const LOD_STATE & state)
    {
        _State = state;
    }

    //--------------------------------------------------------------------------------------------//

    const LOD_STATE & LOD::GetState() const
    {
        return _State;
    }

    //--------------------------------------------------------------------------------------------//

    void LOD::SetData(resource::Object& data)
    {
        _Data = &data;
    }

    //--------------------------------------------------------------------------------------------//

    const resource::Object& LOD::GetData() const
    {
        return *_Data;
    }

    //--------------------------------------------------------------------------------------------//

    resource::Object & LOD::GetData()
    {
        return *_Data;
    }

    //--------------------------------------------------------------------------------------------//

    void LOD::SetParameters(LODParameters& parameters)
    {
        _Parameters = &parameters;
    }

    //--------------------------------------------------------------------------------------------//

    const LODParameters& LOD::GetParameters() const
    {
        return *_Parameters;
    }

    //--------------------------------------------------------------------------------------------//

    LODParameters& LOD::GetParameters()
    {
        return *_Parameters;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool LOD::IsLoaded() const
    {
        return _State==LOD_STATE_Loaded;
    }

    //--------------------------------------------------------------------------------------------//

    bool LOD::HasData() const
    {
        return (_Data != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool LOD::HasParameters() const
    {
        return (_Parameters != NULL);
    }

}
}
//------------------------------------------------------------------------------------------------//

#include "kernel/storage/physical/storage_physical_system.h"
#include "kernel/storage/physical/storage_physical_system_windows.hpp"
#include "kernel/storage/physical/storage_physical_system_unix.hpp"
#include "coffee.h"

namespace coffee
{
namespace storage
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(PhysicalSystem);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PhysicalSystem::PhysicalSystem()
    {
        COFFEE_CreateSingleton(PhysicalSystem);
        _RootFolder.Set(Engine::Get().GetApplicationPath());
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalSystem::~PhysicalSystem()
    {
        COFFEE_DestroySingleton(PhysicalSystem);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const PhysicalPath& PhysicalSystem::GetRootFolder() const
    {
        return _RootFolder;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool PhysicalSystem::IsValidName(const basic::String& file_name) const
    {
        if (file_name.GetLength()==0)
            return false;
        for (uint32 index=0 ; index<file_name.GetLength() ; ++index)
        {
            if (!((file_name[index]>='0' && file_name[index]<='9')
                || (file_name[index]>='a' && file_name[index]<='z')
                || (file_name[index]>='A' && file_name[index]<='Z')
                || file_name[index]=='_' || file_name[index]=='-'
                || file_name[index]=='+'
                || file_name[index]=='.'))
            {
                return false;
            }
        }
        return true;
    }

}
}

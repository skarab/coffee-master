#ifndef _COFFEE_STORAGE_PHYSICAL_PATH_H_
#define _COFFEE_STORAGE_PHYSICAL_PATH_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/alpha/basic_alpha.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Physical file path
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PhysicalPath : public basic::String
    {
        COFFEE_Type(PhysicalPath);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PhysicalPath();
        PhysicalPath(const char* path);
        PhysicalPath(const basic::String& path);
        PhysicalPath(const PhysicalPath& path);
        ~PhysicalPath();

        //-OPERATORS------------------------------------------------------------------------------//

        PhysicalPath& operator=(const char* path);
        PhysicalPath& operator =(const basic::String& path);
        PhysicalPath& operator =(const PhysicalPath& path);

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasPath() const;
        PhysicalPath GetPath() const;
        bool IsFilePath() const;
        basic::String GetFileName() const;
        basic::String GetFileExtension() const;
        basic::String GetFileNameWithoutExtension() const;
        basic::Text GetHierarchy() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Set(const basic::String& path);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PhysicalPath);
}
}
#endif

#ifndef _COFFEE_STORAGE_PATH_H_
#define _COFFEE_STORAGE_PATH_H_

#include "coffee_includes.h"
#include "kernel/basic/alpha/string/basic_string.h"
#include "kernel/basic/alpha/text/basic_text.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Logical path
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Path : public basic::String
    {
        COFFEE_Type(Path);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Path();
        Path(const char* path);
        Path(const basic::String& path);
        Path(const Path& path);
        virtual ~Path();

        //-OPERATORS------------------------------------------------------------------------------//

        Path& operator =(const char* path);
        Path& operator =(const basic::String& path);
        Path& operator =(const Path& path);
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool HasPath() const;
        Path GetPath() const;
        basic::String GetName() const;
        bool IsFilePath() const;
        basic::String GetFileName() const;
        basic::String GetFileExtension() const;
        basic::String GetFileNameWithoutExtension() const;
        basic::Text GetHierarchy() const;
        storage::Path GetHeadFilePath(const basic::String& extension) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetFileExtension(const basic::String& extension);
        void Set(const basic::String& path);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Path);
}
}
#endif

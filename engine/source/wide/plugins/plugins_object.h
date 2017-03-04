#ifndef _COFFEE_PLUGINS_OBJECT_H_
#define _COFFEE_PLUGINS_OBJECT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "wide/plugins/plugins_library.h"

namespace coffee
{
namespace plugins
{
    //--------------------------------------------------------------------------------------------//
    /// Plugin resource object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Object : public resource::Object
    {
        COFFEE_Resource(Object);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Object();
        virtual ~Object();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetLibraryPath(const storage::Path& path) { _LibraryPath = path; }
        const storage::Path& GetLibraryPath() const { return _LibraryPath; }
        const Library& GetLibrary() const;
        Library& GrabLibrary();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsReady() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Initialize();
        void _Finalize();
        bool _LoadLibrary();
        bool _UnloadLibrary();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        #include "wide/plugins/plugins_object_windows.h"

        storage::Path _LibraryPath;
        resource::Property< Library* > _Library;

    public:

        static COFFEE_STATIC_API Library* _Loading;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Object);
}
}
#endif

#ifndef _COFFEE_DAG_PATH_H_
#define _COFFEE_DAG_PATH_H_

#include "kernel/storage/logical/storage_path.h"

namespace coffee
{
namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Scene path
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Path : public storage::Path
    {
        COFFEE_Type(Path);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Path(storage::Path path="");
        ~Path();

        //-OPERATORS------------------------------------------------------------------------------//

        Path& operator =(const Path& path);

        //-ACCESSORS------------------------------------------------------------------------------//

        const storage::Path& GetScenePath() const { return _ScenePath; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsValid() const;
        storage::Path GetNodePath() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Update();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _ScenePath;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Path);
}
}
#endif

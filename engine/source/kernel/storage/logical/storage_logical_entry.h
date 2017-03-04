#ifndef _COFFEE_STORAGE_LOGICAL_ENTRY_H_
#define _COFFEE_STORAGE_LOGICAL_ENTRY_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/storage/logical/storage_path.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Logical entry
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API LogicalEntry : public basic::TreeNode<LogicalEntry>
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        LogicalEntry();
        virtual ~LogicalEntry();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(const basic::String& name);
        const basic::String& GetName() const;

        //-QUERIES--------------------------------------------------------------------------------//

        LogicalEntry* FindChild(const basic::String& child_name);

        void List(basic::Prow<LogicalEntry*>& entry_array, bool it_has_to_list_folders,
            bool it_has_to_list_files, bool it_is_recursive=false);

        Path GetPath() const;
        virtual bool IsFile() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
    };
}
}
#endif

#ifndef _COFFEE_BASIC_CONTAINER_H_
#define _COFFEE_BASIC_CONTAINER_H_

#include "coffee_includes.h"
#include "kernel/meta/array/meta_array.h"
#include "kernel/basic/container/basic_container_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Base class for all serializable containers
    ///
    /// @see coffee::meta::Array
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API Container : public meta::Array
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Container() {};
        virtual ~Container() {};

        //-OPERATORS------------------------------------------------------------------------------//

        virtual const type& operator [](uint32 item_index) const = 0;
        virtual type& operator [](uint32 item_index) = 0;

        //-QUERIES--------------------------------------------------------------------------------//

        virtual uint32 FindItem(const type& item) const = 0;
        
        const type& GetFirst() const
        {
            COFFEE_Assert(GetSize()>0, core::ERROR_CODE_IncorrectUsage, "No items in the container!");
            return (*this)[0];
        }

        type& GetFirst(uint32 item_index)
        {
            COFFEE_Assert(GetSize()>0, core::ERROR_CODE_IncorrectUsage, "No items in the container!");
            return (*this)[0];
        }

        const type& GetLast() const
        {
            COFFEE_Assert(GetSize()>0, core::ERROR_CODE_IncorrectUsage, "No items in the container!");
            return (*this)[GetSize()-1];
        }

        type& GetLast()
        {
            COFFEE_Assert(GetSize()>0, core::ERROR_CODE_IncorrectUsage, "No items in the container!");
            return (*this)[GetSize()-1];
        }

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual uint32 Add(uint32 index = NONE) = 0;
        virtual uint32 AddItem(type item, uint32 index = NONE) = 0;
        virtual void Remove(uint32 index = NONE) = 0;
        virtual void RemoveItem(type item) = 0;
        virtual void Resize(uint32 count) = 0;
        virtual void Clear() = 0;
        virtual void Erase() = 0;

        virtual const void* GetLinearBuffer() const = 0;
        virtual void* GetLinearBuffer() = 0;
        virtual const void* GetItemPointer(uint32 index) const = 0;
        virtual void* GetItemPointer(uint32 index) = 0;
    };
}
}
#endif

#ifndef _COFFEE_RESOURCE_HANDLER_H_
#define _COFFEE_RESOURCE_HANDLER_H_

#include "coffee_includes.h"
#include "kernel/resource/handler/resource_handler_template.h"
#include "kernel/resource/handler/resource_handler_state.h"
#include "kernel/resource/resource_object.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource handler
    ///
    /// Its an helper that you may attach to a resource::Object, to get notifications about
    /// loading states (ex: if you wish to trigger something when your resource is reloaded).
    /// 
    /// @note It doesnt store a reference, not its serializable, its an helper you attach
    /// to an already existing resource::Object.
    //--------------------------------------------------------------------------------------------//
    template< typename resource_object > \
    class COFFEE_TEMPLATE_API Handler
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Handler();
        Handler(resource_object* resource);
        ~Handler();

        //-OPERATORS------------------------------------------------------------------------------//

        Handler<resource_object>& operator = (const Handler<resource_object>& other);

        //-ACCESSORS------------------------------------------------------------------------------//

        void Set(resource_object* resource);
        const resource_object& Get() const;
        resource_object& Get();
        HANDLER_STATE GetState() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        HANDLER_STATE Update();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource_object* _Resource;
        HANDLER_STATE _State;
        uint32 _Stamp;
    };

    #include "kernel/resource/handler/resource_handler.hpp"
}
}
#endif

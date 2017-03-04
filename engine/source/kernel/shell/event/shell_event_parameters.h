#ifndef _COFFEE_SHELL_EVENT_PARAMETERS_H_
#define _COFFEE_SHELL_EVENT_PARAMETERS_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace shell
{
    class EventHandler;

    //--------------------------------------------------------------------------------------------//
    /// Event parameters
    ///
    /// Class to support custom parameters attached to events.
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EventParameters
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EventParameters(void* custom_parameter=NULL, meta::Object* object_parameter=NULL);
        EventParameters(const EventParameters& parameters);
        ~EventParameters();

        //-OPERATORS------------------------------------------------------------------------------//

        EventParameters& operator = (const EventParameters& parameters);
        bool operator == (const EventParameters& parameters) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetCustomParameter(void* custom_parameter);
        const void* GetCustomParameter() const;
        void SetParameter(meta::Object* object_parameter);
        const meta::Object* GetParameter() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        void* _CustomParameter;
        meta::Object* _Parameter;
    };
}
}
#endif

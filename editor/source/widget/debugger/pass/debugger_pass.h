#ifndef _EDITOR_DEBUGGER_PASS_H_
#define _EDITOR_DEBUGGER_PASS_H_

#include "coffee_editor_includes.h"
#include "widget/debugger/pass/debugger_pass_type.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Debugger pass
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API DebuggerPass : public graphics::FramePass
    {
        COFFEE_Type(DebuggerPass);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DebuggerPass();
        ~DebuggerPass();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetPassType(DEBUGGER_PASS_TYPE type);
        DEBUGGER_PASS_TYPE GetPassType() const { return _PassType; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(graphics::FramePass* previous_pass);
        void Finalize(graphics::FramePass* previous_pass);
        void Render(graphics::Viewport& viewport, graphics::FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        DEBUGGER_PASS_TYPE _PassType;
        graphics::FrameLayerBGRA* _Layer;
        graphics::Material _Material;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, DebuggerPass);
}
}
#endif

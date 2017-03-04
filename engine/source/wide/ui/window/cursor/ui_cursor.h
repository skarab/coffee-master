#ifndef _COFFEE_UI_CURSOR_H_
#define _COFFEE_UI_CURSOR_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/window/drag_context/ui_drag_context.h"
#include "wide/ui/skin/ui_skin_icon.h"
#include "system/graphics/texture/graphics_texture.h"
#include "system/input/input.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// UI Cursor
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Cursor : public input::Handler
    {
        friend class Window;
        
        COFFEE_Type(Cursor);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Cursor();
        virtual ~Cursor();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetIcon(const SKIN_ICON& icon);
        void SetIcon(graphics::Texture icon);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void BeginCapture();
        void EndCapture();
        void Update();
        void Draw();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Cursor);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        COFFEE_Event bool OnKeyReleased(shell::Event& event);
        COFFEE_Event bool OnCharacterKeyPressed(shell::Event& event);
        COFFEE_Event bool OnMouseMove(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        COFFEE_Event bool OnMouseDoubleClick(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonReleased(shell::Event& event);
        COFFEE_Event bool OnCommand(shell::Event& event);
        
        bool OnDropFiles(const basic::Vector<storage::PhysicalPath>& files,
            const basic::Vector2i& position);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _IsResizingAvailable(const Window& window, uint32 hit) const;

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        DragContext* _DragContext;
        bool _ItIsResizing;
        uint32 _HitTestResult;
        Window* _HitWindow;
        Window* _HitItem;
        Window* _DragItem;
        Window* _DropItem;
        bool _ItIsCapturing;
        graphics::Texture _Icon;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Cursor);
}
}
#endif

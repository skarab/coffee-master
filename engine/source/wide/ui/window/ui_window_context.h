#ifndef _COFFEE_UI_WINDOW_CONTEXT_H_
#define _COFFEE_UI_WINDOW_CONTEXT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/window/ui_window.h"

namespace coffee
{
namespace ui
{
    class Skin;

    //--------------------------------------------------------------------------------------------//
    /// Window context
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API WindowContext
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        WindowContext();
        virtual ~WindowContext();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::Rectangle& GetDesktopClipRect() const;
        const basic::Rectangle& GetDesktopWindowRect() const;
        void SetSkin(Skin* skin);
        const Skin& GetSkin() const;
        Skin& GetSkin();

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasSkin() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(const Window* window=NULL, const WindowContext* parent_context=NULL);
        void Set(const basic::Vector2i& position, const basic::Vector2i& size);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector2i _DesktopToParentClientTranslation;
        basic::Vector2i _ParentClientToWindowTranslation;
        basic::Vector2i _ParentClientSize;
        basic::Vector2i _WindowToClientTranslation;
        basic::Vector2i _ClientSize;
        basic::Rectangle _DesktopClipRect;
        basic::Rectangle _DesktopWindowRect;
        Skin* _Skin;
    };
}
}
#endif

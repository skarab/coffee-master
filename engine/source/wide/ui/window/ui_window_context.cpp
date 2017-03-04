#include "wide/ui/window/ui_window_context.h"
#include "wide/ui/skin/ui_skin.h"

namespace coffee
{
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    WindowContext::WindowContext()
    {
    }

    //--------------------------------------------------------------------------------------------//

    WindowContext::~WindowContext()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::Rectangle& WindowContext::GetDesktopClipRect() const
    {
        return _DesktopClipRect;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Rectangle& WindowContext::GetDesktopWindowRect() const
    {
        return _DesktopWindowRect;
    }

    //--------------------------------------------------------------------------------------------//

    void WindowContext::SetSkin(Skin* skin)
    {
        _Skin = skin;
    }

    //--------------------------------------------------------------------------------------------//

    const Skin& WindowContext::GetSkin() const
    {
        return *_Skin;
    }

    //--------------------------------------------------------------------------------------------//

    Skin& WindowContext::GetSkin()
    {
        return *_Skin;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool WindowContext::HasSkin() const
    {
        return (_Skin!=NULL);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void WindowContext::Create(const Window* window, const WindowContext* parent_context)
    {
        if(window==NULL)
        {
            _DesktopToParentClientTranslation.Set(0, 0);
            _ParentClientToWindowTranslation.Set(0, 0);
            _ParentClientSize.Set(32000, 32000);
            _WindowToClientTranslation.Set(0, 0);
            _ClientSize.Set(32000, 32000);
            _DesktopClipRect.Position = _DesktopToParentClientTranslation;
            _DesktopClipRect.Size = _ParentClientSize;
            _DesktopWindowRect.Position = basic::Vector2i();
            _DesktopWindowRect.Size = basic::Vector2i(32000, 32000);
            _Skin = NULL;
        }
        else
        {
            if(parent_context==NULL)
            {
                const Window* parent_window(NULL);
                bool it_has_to_clip(true);

                _DesktopToParentClientTranslation.Set(0, 0);
                _ParentClientToWindowTranslation = window->GetPosition();
                _WindowToClientTranslation = window->GetClientRect().Position;
                _ClientSize = window->GetClientRect().Size;
                _DesktopClipRect.Position = _DesktopToParentClientTranslation;

                if (window->HasStyle(WINDOW_STYLE_NoParentClip))
                {
                    _DesktopClipRect.Position = basic::Vector2i(0, 0);
                    it_has_to_clip = false;
                    _ParentClientSize.Set(32000, 32000);

                    if(window->HasParent())
                        parent_window = &window->GetParentWindow();
                }
                else
                {
                    if (window->HasParent())
                    {
                        parent_window = &window->GetParentWindow();
                        _ParentClientSize = parent_window->GetClientRect().Size;
                    }
                    else
                    {
                        _ParentClientSize.Set(32000, 32000);
                    }
                }

                _DesktopClipRect.Size = _ParentClientSize;

                uint32 parent_count(0);
                basic::Vector2i clipped_desktop_pos(0);

                while (parent_window!=NULL)
                {
                    clipped_desktop_pos += parent_window->GetPosition() + parent_window->GetClientRect().Position;
                    _DesktopToParentClientTranslation += parent_window->GetPosition() + parent_window->GetClientRect().Position;
                    
                    if (!window->HasStyle(WINDOW_STYLE_NoParentClip))
                        _DesktopClipRect.Position = clipped_desktop_pos;

                    basic::Rectangle parent_clip_rect;

                    parent_clip_rect.Position = parent_window->GetPosition() + parent_window->GetClientRect().Position;
                    parent_clip_rect.Size = parent_window->GetClientRect().Size;

                    if (window->HasStyle(WINDOW_STYLE_NoParentClientClip) && parent_count==0)
                    {
                    }
                    else if (it_has_to_clip)
                    {
                        if (parent_clip_rect.IsEmpty())
                        {
                            _DesktopClipRect.SetEmpty();
                        }
                        else
                        {
                            _DesktopClipRect -= parent_clip_rect;
                        }

                        clipped_desktop_pos = _DesktopClipRect.Position;
                    }

                    if (parent_window->HasParent())
                    {
                        if (parent_window->HasStyle(WINDOW_STYLE_NoParentClip))
                            it_has_to_clip = false;

                        parent_window = &parent_window->GetParentWindow();
                        ++parent_count;
                    }
                    else
                    {
                        parent_window = NULL;
                    }
                }

                _DesktopWindowRect.Position = _DesktopToParentClientTranslation + _ParentClientToWindowTranslation;
                _DesktopWindowRect.Size = window->GetSize();

                if(window->HasSkin())
                {
                    _Skin = (Skin*) &window->GetSkin();
                }
                else
                {
                    _Skin = NULL;
                }
            }
            else
            {
                _DesktopToParentClientTranslation = parent_context->_DesktopToParentClientTranslation
                    + parent_context->_ParentClientToWindowTranslation + parent_context->_WindowToClientTranslation;
                _ParentClientToWindowTranslation = window->GetPosition();
                _ParentClientSize = parent_context->_ClientSize;
                _WindowToClientTranslation = window->GetClientRect().Position;
                _ClientSize = window->GetClientRect().Size;

                if(window->HasStyle(WINDOW_STYLE_NoParentClip))
                {
                    _DesktopClipRect.Position = basic::Vector2i(0, 0);
                    _DesktopClipRect.Size = basic::Vector2i(32000, 32000);
                }
                else if(window->HasStyle(WINDOW_STYLE_NoParentClientClip))
                {
                    _DesktopClipRect = parent_context->_DesktopClipRect;
                }
                else
                {
                    _DesktopClipRect.Position = _DesktopToParentClientTranslation;
                    _DesktopClipRect.Size = _ParentClientSize;

                    if(parent_context->_DesktopClipRect.IsEmpty())
                    {
                        _DesktopClipRect.SetEmpty();
                    }
                    else
                    {
                        _DesktopClipRect -= parent_context->_DesktopClipRect;
                    }
                }

                _DesktopWindowRect.Position = _DesktopToParentClientTranslation+_ParentClientToWindowTranslation;
                _DesktopWindowRect.Size = window->GetSize();

                if(window->HasSkin())
                {
                    _Skin = (Skin *) &window->GetSkin();
                }
                else if(parent_context->HasSkin())
                {
                    _Skin = (Skin *) &parent_context->GetSkin();
                }
                else
                {
                    _Skin = NULL;
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void WindowContext::Set(const basic::Vector2i& position, const basic::Vector2i& size)
    {
        _DesktopToParentClientTranslation.Set(0, 0);
        _ParentClientToWindowTranslation = position;
        _ParentClientSize.Set(32000, 32000);
        _WindowToClientTranslation.Set(0, 0);
        _ClientSize.Set(32000, 32000);
        _DesktopClipRect.Position = position;
        _DesktopClipRect.Size = size;
        _DesktopWindowRect.Position = position;
        _DesktopWindowRect.Size = size;
    }

}
}

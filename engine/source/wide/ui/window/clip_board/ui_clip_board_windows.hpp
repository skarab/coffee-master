//------------------------------------------------------------------------------------------------//
/// @file wide/ui/window/clip_board/ui_clip_board_windows.hpp
//------------------------------------------------------------------------------------------------//
#ifdef COFFEE_OS_WINDOWS

//-INCLUDES---------------------------------------------------------------------------------------//
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace ui
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    void ClipBoard::CopyText(const basic::Text& text)
    {
        LPTSTR lptstrCopy;
        HGLOBAL hglbCopy;

        _Text = text;

        if(OpenClipboard(graphics::Device::Get().GetPlatformWindow()))
        {
            EmptyClipboard();

            if(text.GetLineCount() > 0)
            {
                char * text_buffer = text.GenerateTextBuffer();
                uint32 size = strlen(text_buffer) + 1;

                hglbCopy = GlobalAlloc(GMEM_MOVEABLE, size * sizeof(char));

                if(hglbCopy != NULL)
                {
                    lptstrCopy = (LPTSTR) GlobalLock(hglbCopy);
                    memcpy(lptstrCopy, text_buffer, size * sizeof(char));
                    GlobalUnlock(hglbCopy);
                    SetClipboardData(CF_TEXT, hglbCopy);
                }

                COFFEE_Free(text_buffer);
            }

            CloseClipboard();
        }
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Text& ClipBoard::PasteText()
    {
        HGLOBAL hglb;
        LPTSTR lptstr;

        _Text.SetEmpty();

        if(IsClipboardFormatAvailable(CF_TEXT)
            && OpenClipboard(graphics::Device::Get().GetPlatformWindow())
           )
        {
            hglb = GetClipboardData(CF_TEXT);

            if(hglb != NULL)
            {
                lptstr = (LPTSTR) GlobalLock(hglb);

                if(lptstr != NULL)
                {
                    _Text.Set((const char *) lptstr);
                    GlobalUnlock(hglb);
                }
            }

            CloseClipboard();

            return _Text;
        }

        return _Text;
    }

}
}
#endif
//------------------------------------------------------------------------------------------------//

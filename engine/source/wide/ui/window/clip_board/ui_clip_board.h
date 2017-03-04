#ifndef _COFFEE_UI_CLIP_BOARD_H_
#define _COFFEE_UI_CLIP_BOARD_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// ClipBoard
    ///
    /// Used by EditBox and TextBox to copy & paste text from OS clipboard.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ClipBoard
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ClipBoard();
        ~ClipBoard();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CopyText(const basic::Text& text);
        const basic::Text& PasteText();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Text _Text;
    };
}
}
#endif

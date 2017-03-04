#ifndef _COFFEE_BASIC_ALPHA_TEXT_H_
#define _COFFEE_BASIC_ALPHA_TEXT_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/container/list/basic_list.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Text class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Text : public meta::Object
    {
        COFFEE_Type(Text);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Text();
        Text(const Text& text);
        ~Text();

        //-OPERATORS------------------------------------------------------------------------------//

        const String& operator [](uint32 line_index) const;
        String& operator [](uint32 line_index);
        Text& operator =(const Text& text);
        Text& operator +=(const Text& text);
        Text operator+(const Text& text) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetLineCount() const;
        const String& GetLine(uint32 line_index) const;
        String& GetLine(uint32 line_index);

        //-QUERIES--------------------------------------------------------------------------------//

        char* GenerateTextBuffer() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void AddLine(const String& line, uint32 line_index=NONE);
        void RemoveLine(uint32 line_index);
        void SetEmpty();
        void Set(const char* text_buffer, uint32 size=NONE);
        void Log() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        List< String > _LineArray;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Text);
}
}
#endif

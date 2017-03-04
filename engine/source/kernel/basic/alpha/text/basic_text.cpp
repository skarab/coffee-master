#include "kernel/basic/alpha/text/basic_text.h"
#include "kernel/core/core.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Text);
        COFFEE_Attribute(basic::List< basic::String >, _LineArray, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Text::Text()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Text::Text(const Text & text)
    {
        this->operator =(text);
    }

    //--------------------------------------------------------------------------------------------//

    Text::~Text()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    const String & Text::operator [](uint32 index) const
    {
        return GetLine(index);
    }

    //--------------------------------------------------------------------------------------------//

    String & Text::operator [](uint32 index)
    {
        return GetLine(index);
    }

    //--------------------------------------------------------------------------------------------//

    Text & Text::operator =(const Text & text)
    {
        _LineArray = text._LineArray;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Text & Text::operator +=(const Text & text)
    {
        for(uint32 index = 0 ; index < text.GetLineCount() ; index ++)
            AddLine(text.GetLine(index));

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Text Text::operator +(const Text & text) const
    {
        Text output(*this);
        output += text;
        return output;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 Text::GetLineCount() const
    {
        return _LineArray.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    const String & Text::GetLine(uint32 line_index) const
    {
        return _LineArray[ line_index ];
    }

    //--------------------------------------------------------------------------------------------//

    String & Text::GetLine(uint32 line_index)
    {
        return _LineArray[ line_index ];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    char * Text::GenerateTextBuffer() const
    {
        char * buffer = NULL;
        uint32 buffer_size = 0;
        uint32 buffer_index = 0;

        for(uint32 index = 0 ; index < _LineArray.GetSize() ; index ++)
        {
            buffer_size += _LineArray[ index ].GetLength() + 1;
            buffer = (char *) COFFEE_Reallocate(buffer, buffer_size);
            COFFEE_Copy(buffer + buffer_index, _LineArray[index].GetBuffer(), _LineArray[index].GetLength());

            if(index < _LineArray.GetSize() - 1) buffer[ buffer_size - 1 ] = '\n';
            else buffer[ buffer_size - 1 ] = NULL_CHAR;

            buffer_index = buffer_size;
        }

        return buffer;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Text::AddLine(const String & line, uint32 line_index)
    {
        _LineArray.AddItem(line, line_index);
    }

    //--------------------------------------------------------------------------------------------//

    void Text::RemoveLine(uint32 line_index)
    {
        _LineArray.Remove(line_index);
    }

    //--------------------------------------------------------------------------------------------//

    void Text::SetEmpty()
    {
        _LineArray.Erase();
    }

    //--------------------------------------------------------------------------------------------//

    void Text::Set(const char * text_buffer, uint32 size)
    {
        String line;
        uint32 index = 0;

        SetEmpty();

        if(text_buffer==NULL || size==0)
            return;

        while((size==NONE || index<size) && text_buffer[index]!=NULL_CHAR)
        {
            if(text_buffer[index]=='\n' || text_buffer[index]=='\r')
            {
                _LineArray.AddItem(line);
                line.SetEmpty();

                if(text_buffer[index]=='\r')
                    ++index;
            }
            else
            {
                line += text_buffer[index];
            }

            ++index;
        }

        if(line.GetLength() > 0)
            _LineArray.AddItem(line);
    }

    //--------------------------------------------------------------------------------------------//

    void Text::Log() const
    {
        for(uint32 index = 0 ; index < GetLineCount() ; index ++)
            COFFEE_Log(core::Log::None, "%s\n", GetLine(index).GetBuffer());
    }

}
}

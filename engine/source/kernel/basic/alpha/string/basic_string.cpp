#include "kernel/basic/alpha/string/basic_string.h"
#include "kernel/core/core.h"
#include "kernel/basic/container/vector/basic_vector.h"
#include "kernel/meta/meta.h"

#define COFFEE_DEBUG_STRING_MEMORY_LEAKS 0

#if COFFEE_DEBUG_STRING_MEMORY_LEAKS
    #define STRING_Allocate COFFEE_Allocate
    #define STRING_Reallocate COFFEE_Reallocate
    #define STRING_Free COFFEE_Free
#else
    #define STRING_Allocate malloc
    #define STRING_Reallocate realloc
    #define STRING_Free free
#endif

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::String);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    String::String() :
        _Buffer(NULL),
        _ReservedSize(0)
    {
        SetLength(0);
    }

    //--------------------------------------------------------------------------------------------//

    String::String(char c) :
        _Buffer(NULL),
        _ReservedSize(0)
    {
        SetLength(0);
        operator=(c);
    }

    //--------------------------------------------------------------------------------------------//

    String::String(const String & text) :
        _Buffer(NULL),
        _ReservedSize(0)
    {
        SetLength(0);
        operator=(text);
    }

    //--------------------------------------------------------------------------------------------//

    String::String(const char * text, ...) :
        _Buffer(NULL),
        _ReservedSize(0)
    {
        SetLength(0);

        va_list va_array;
        char line[4096];
        va_start(va_array, text);
            _vsnprintf(line, 4096, text, va_array);
        va_end(va_array);
        operator=(line);
    }

    //--------------------------------------------------------------------------------------------//

    String::~String()
    {
        STRING_Free(_Buffer);
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    char String::operator[](uint32 char_index) const
    {
        return GetBuffer()[char_index];
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator=(char c)
    {
        SetLength(1);
        GetBuffer()[0] = c;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator=(const char* text)
    {
        SetLength((uint32)strlen(text));
        COFFEE_Copy(GetBuffer(), text, GetLength());
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator=(const String& text)
    {
        SetLength(text.GetLength());
        COFFEE_Copy(GetBuffer(), text.GetBuffer(), GetLength());
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String String::operator+(char c) const
    {
        String string(*this);
        string += c;
        return string;
    }

    //--------------------------------------------------------------------------------------------//

    String String::operator+(const char* text) const
    {
        String string(*this);
        string += text;
        return string;
    }

    //--------------------------------------------------------------------------------------------//

    String String::operator+(const String& text) const
    {
        String string(*this);
        string += text;
        return string;
    }

    //--------------------------------------------------------------------------------------------//
    
    String String::operator - (uint32 remove_count) const
    {
        String string(*this);
        string -= remove_count;
        return string;
    }
        
    //--------------------------------------------------------------------------------------------//

    String& String::operator+=(char c)
    {
        if(c != NULL_CHAR)
        {
            SetLength(GetLength()+1);
            GetBuffer()[GetLength()-1] = c;
        }
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator+=(const char* text)
    {
        uint32 length = (uint32)strlen(text);
        uint32 old_length = GetLength();
        SetLength(GetLength() + length);
        COFFEE_Copy(GetBuffer() + old_length, text, length);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator+=(const String& text)
    {
        uint32 length = GetLength();
        SetLength(GetLength()+text.GetLength());
        COFFEE_Copy(GetBuffer()+length, text.GetBuffer(), text.GetLength());
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator--()
    {
        operator-=(1);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    String& String::operator-=(uint32 remove_count)
    {
        if(remove_count>GetLength())
            remove_count = GetLength();

        SetLength(GetLength()-remove_count);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator==(char c) const
    {
        return (GetLength()==1 && GetBuffer()[0]==c);
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator==(const char* text) const
    {
        if (GetLength()!=strlen(text))
            return false;

        for (uint32 index=0 ; index<GetLength() ; ++index)
            if (GetBuffer()[index] != text[index])
                return false;

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator==(const String & text) const
    {
        if(GetLength() != text.GetLength())
            return false;

        for(uint32 index = 0 ; index < GetLength() ; ++index)
            if(GetBuffer()[ index ] != text.GetBuffer()[ index ])
                return false;

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator!=(char c) const
    {
        return !operator==(c);
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator!=(const char * text) const
    {
        return !operator==(text);
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator!=(const String & text) const
    {
        return !operator==(text);
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator < (const String& text) const
    {
        return strcmp(GetBuffer(), text.GetBuffer())<0;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::operator > (const String& text) const
    {
        return strcmp(GetBuffer(), text.GetBuffer())>0;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool String::IsContaining(char c) const
    {
        for (uint32 index=0 ; index<GetLength() ; ++index)
            if (GetBuffer()[index]==c)
                return true;
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsContaining(const char* text) const
    {
        uint32 length = (uint32)strlen(text);

        if (GetLength()<length || length==0)
            return false;

        uint32 index_found = 0;
        bool found = false;

        for (uint32 index=0 ; index<GetLength() ; ++index)
        {
            if (found)
            {
                if (GetBuffer()[index]!=text[index-index_found])
                    found = false;
                else if (index-index_found==length-1)
                    return true;
            }
            else
            {
                if (GetBuffer()[index]==text[0])
                {
                    found = true;
                    index_found = index;

                    if (length==1)
                        return true;
                }
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsContaining(const String & text) const
    {
        if(GetLength() < text.GetLength() || text.GetLength() == 0)
            return false;

        uint32 index_found = 0;
        bool found = false;;

        for(uint32 index = 0 ; index < GetLength() ; index ++)
        {
            if(found)
            {
                if(GetBuffer()[ index ] != text.GetBuffer()[ index - index_found ])
                    found = false;
                else if(index - index_found == text.GetLength() - 1)
                    return true;
            }
            else
            {
                if(GetBuffer()[ index ] == text.GetBuffer()[ 0 ])
                {
                    found = true;
                    index_found = index;

                    if(text.GetLength() == 1)
                        return true;
                }
            }
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsSuffixed(const char * suffix) const
    {
        uint32 suffix_length;

        suffix_length = (uint32) strlen(suffix);

        if(suffix_length > GetLength())
            return false;

        for(uint32 index = 0 ; index < suffix_length ; index ++)
            if(suffix[ index ] != _Buffer[ GetLength() - suffix_length + index ])
                return false;

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsSuffixed(const String & suffix) const
    {
        if(suffix.GetLength() > GetLength())
            return false;

        for(uint32 index = 0 ; index < suffix.GetLength() ; index ++)
            if(suffix[ index ] != _Buffer[ GetLength() - suffix.GetLength() + index ])
                return false;

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsPrefixed(const char * prefix) const
    {
        uint32 prefix_length;

        prefix_length = (uint32) strlen(prefix);

        if(prefix_length > GetLength())
            return false;

        for(uint32 index = 0 ; index < prefix_length ; index ++)
            if(prefix[ index ] != _Buffer[ index ])
                return false;

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsPrefixed(const String & prefix) const
    {
        if(prefix.GetLength() > GetLength())
            return false;

        for(uint32 index = 0 ; index < prefix.GetLength() ; index ++)
            if(prefix[ index ] != _Buffer[ index ])
                return false;

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    char String::GetFirst() const
    {
        COFFEE_Assert(GetLength()>0, core::ERROR_CODE_IncorrectUsage, "The string is empty!");
        return (*this)[0];
    }
    
    //--------------------------------------------------------------------------------------------//

    char String::GetLast() const
    {
        COFFEE_Assert(GetLength()>0, core::ERROR_CODE_IncorrectUsage, "The string is empty!");
        return (*this)[GetLength()-1];
    }
        
    //--------------------------------------------------------------------------------------------//

    String String::GetLeft(uint32 length) const
    {
        if (length>=GetLength())
            return *this;
        String word;
        for (uint32 index=0 ; index<length ; ++index)
            word += GetBuffer()[index];
        return word;
    }

    //--------------------------------------------------------------------------------------------//

    String String::GetRight(uint32 length) const
    {
        if (length>=GetLength())
            return *this;
        return &GetBuffer()[GetLength()-length];
    }

    //--------------------------------------------------------------------------------------------//

    String String::GetCenter(uint32 start, uint32 stop) const
    {
        String left_string;
        left_string = GetLeft(stop+1);
        if (start>=left_string.GetLength())
            return String();
        return left_string.GetRight(left_string.GetLength()-start);
    }

    //--------------------------------------------------------------------------------------------//

    bool String::GetNextWord(String & word, int32 & last_index) const
    {
        word = "";

        if((uint32) last_index != NONE && _Buffer[ last_index ] == NULL_CHAR)
            return false;

        while(1)
        {
            last_index ++;

            if(_Buffer[ last_index ] == NULL_CHAR)
                return true;

            if(_Buffer[ last_index ] == ' ' || _Buffer[ last_index ] == '\t' || _Buffer[ last_index ] == '\n')
            {
                while(_Buffer[ last_index + 1 ] == ' ' || _Buffer[ last_index + 1 ] == '\t' || _Buffer[ last_index + 1 ] == '\n')
                {
                    last_index ++;

                    if(_Buffer[ last_index ] == NULL_CHAR)
                        return true;
                }

                break;
            }

            word += _Buffer[ last_index ];
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::GetNextWord(String & word, int32 & last_index, char token) const
    {
        word = "";

        if((uint32) last_index != NONE && _Buffer[ last_index ] == NULL_CHAR)
            return false;

        while(1)
        {
            last_index ++;

            if(_Buffer[ last_index ] == NULL_CHAR)
                return true;

            if(_Buffer[ last_index ] == token)
            {
                while(_Buffer[ last_index + 1 ] == token)
                {
                    last_index ++;

                    if(_Buffer[ last_index ] == NULL_CHAR)
                        return true;
                }

                break;
            }

            word += _Buffer[ last_index ];
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::GetNextWord(String & word, int32 & last_index, const Vector< String > & token_array) const
    {
        word = "";

        if((uint32) last_index != NONE && _Buffer[ last_index ] == NULL_CHAR)
            return false;

        while(1)
        {
            ++last_index;

            if (_Buffer[last_index]==NULL_CHAR)
                return true;

            bool token = false;
            uint32 tindex = NONE;
            do
            {
                tindex = NONE;
                for (uint32 i=0 ; i<token_array.GetSize() ; ++i)
                {
                    if (token_array[i][0]==_Buffer[token?last_index+1:last_index])
                    {
                        tindex = i;
                        break;
                    }
                }

                if (tindex!=NONE)
                {
                    if (token && _Buffer[++last_index]==NULL_CHAR)
                        return true;
                    token = true;
                }
            }
            while (tindex!=NONE);
            if (token)
                break;

            word += _Buffer[last_index];
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 String::GetOccurencesCount(char c) const
    {
        uint32 occurences_count = 0;

        for(uint32 index = 0 ; index < GetLength() ; index ++)
        {
            if(GetBuffer()[ index ] == c)
                occurences_count ++;
        }

        return occurences_count;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 String::GetOccurencesCount(const String& word) const
    {
        uint32 occurences_count = 0;

        for(uint32 index = 0 ; index < GetLength() ; index ++)
        {
            if(GetCenter(index, index + word.GetLength() - 1) == word)
                occurences_count ++;
        }

        return occurences_count;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 String::Find(char c) const
    {
        for (uint32 index=0 ; index<GetLength() ; ++index)
            if (GetBuffer()[index]==c)
                return index;
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 String::FindLast(char c) const
    {
        for (uint32 index=0 ; index<GetLength() ; ++index)
            if (GetBuffer()[GetLength()-index-1]==c)
                return GetLength()-index-1;
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 String::Find(const String& word) const
    {
        if (word.GetLength()>0)
        {
            for (uint32 index=0 ; index<GetLength() ; ++index)
                if (GetCenter(index, index+word.GetLength()-1)==word)
                    return index;
        }
        return NONE;
    }
        
    //--------------------------------------------------------------------------------------------//

    int32 String::GetInteger() const
    {
        return (int32)atoi(_Buffer);
    }

    //--------------------------------------------------------------------------------------------//

    real String::GetReal() const
    {
        return (real) atof(_Buffer);
    }

    //--------------------------------------------------------------------------------------------//

    const char* String::GetBuffer() const
    {
        return _Buffer;
    }

    //--------------------------------------------------------------------------------------------//

    char* String::GetBuffer()
    {
        return _Buffer;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 String::GetLength() const
    {
        return _Length;
    }

    //--------------------------------------------------------------------------------------------//

    bool String::IsEmpty() const
    {
        return _Length==0;
    }

    //--------------------------------------------------------------------------------------------//

    basic::String String::ToUpperCase() const
    {
        basic::String text(*this);
        for (uint32 index=0 ; index<text.GetLength() ; ++index)
        {
            if (text[index]>='a' && text[index]<='z')
                text.GetBuffer()[index] = text[index]+'A'-'a';
        }
        return text;
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::String String::ToLowerCase() const
    {
        basic::String text(*this);
        for (uint32 index=0 ; index<text.GetLength() ; ++index)
        {
            if (text[index]>='A' && text[index]<='Z')
                text.GetBuffer()[index] = text[index]+'a'-'A';
        }
        return text;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void String::Set(const char* text, ...)
    {
        SetLength(0);

        va_list va_array;
        char line[ 256 ];
        va_start(va_array, text);
            _vsnprintf(line, 256, text, va_array);
        va_end(va_array);
        operator=(line);
    }

    //--------------------------------------------------------------------------------------------//

    void String::SetLength(uint32 length)
    {
        _Length = length;
        if (length+1>_ReservedSize)
        {
            _ReservedSize = length + length/2 + 2;
            if (_Buffer==NULL) _Buffer = (char*)STRING_Allocate(_ReservedSize);
            else _Buffer = (char*)STRING_Reallocate(_Buffer, _ReservedSize);
        }
        _Buffer[_Length] = NULL_CHAR;
    }

    //--------------------------------------------------------------------------------------------//

    void String::SetEmpty()
    {
        SetLength(0);
    }

    //--------------------------------------------------------------------------------------------//

    void String::Replace(const String& in, const String& out)
    {
        String new_string;
        if( in.GetLength()==0)
            return;
        for (uint32 index=0 ; index<GetLength() ; ++index)
        {
            if (GetCenter(index, index+in.GetLength()-1)==in)
            {
                new_string += out;
                index += in.GetLength()-1;
            }
            else
            {
                new_string += GetBuffer()[index];
            }
        }
        this->operator =(new_string);
    }

    //--------------------------------------------------------------------------------------------//

    void String::CutLeft(uint32 length)
    {
        if (GetLength()<=length)
        {
            SetLength(0);
        }
        else
        {
            String string(*this);
            this->operator =(string.GetBuffer()+length);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void String::CutRight(uint32 length)
    {
        if(GetLength() <= length) SetLength(0);
        else SetLength(GetLength() - length);
    }

    //--------------------------------------------------------------------------------------------//

    void String::Serialize(coffee::meta::Stream& stream)
    {
        uint32 length = _Length+1;
        
        COFFEE_SerializeScalar(&length, uint32);
        if (stream.GetMode()==coffee::storage::MODE_Output)
        {
            stream.GetStream().Push(_Buffer, (ulong)length);
        }
        else
        {
            SetLength(length-1);
            COFFEE_Copy(_Buffer, stream.GetStream().Pop((ulong)length), (ulong)length);
        }
    }

}
}

#undef STRING_Allocate
#undef STRING_Reallocate
#undef STRING_Free

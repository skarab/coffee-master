#ifndef _COFFEE_BASIC_ALPHA_STRING_H_
#define _COFFEE_BASIC_ALPHA_STRING_H_

#include "coffee_includes.h"
#include "kernel/meta/param/meta_params.h"
#include "kernel/basic/container/vector/basic_vector_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Simple string class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API String : public meta::Object
    {
        COFFEE_Type(String);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        String();
        String(char c);
        String(const String& text);
        String(const char* text, ...);
        virtual ~String();

        //-OPERATORS------------------------------------------------------------------------------//

        char operator [] (uint32 char_index) const;
        String& operator = (char c);
        String& operator = (const char* text);
        String& operator = (const String& text);
        String operator + (char c) const;
        String operator + (const char* text) const;
        String operator + (const String& text) const;
        String operator - (uint32 remove_count) const;
        String& operator += (char c);
        String& operator += (const char* text);
        String& operator += (const String& text);
        String& operator -- ();
        String& operator -= (uint32 remove_count);
        bool operator == (char c) const;
        bool operator == (const char* text) const;
        bool operator == (const String& text) const;
        bool operator != (char c) const;
        bool operator != (const char* text) const;
        bool operator != (const String& text) const;
        bool operator < (const String& text) const;
        bool operator > (const String& text) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        const char* GetBuffer() const;
        char* GetBuffer();
        uint32 GetLength() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsEmpty() const;
        bool IsContaining(char c) const;
        bool IsContaining(const char* text) const;
        bool IsContaining(const String& text) const;
        bool IsSuffixed(const char* suffix) const;
        bool IsSuffixed(const String& suffix) const;
        bool IsPrefixed(const char* prefix) const;
        bool IsPrefixed(const String& prefix) const;
        char GetFirst() const;
        char GetLast() const;
        String GetLeft(uint32 length) const;
        String GetRight(uint32 length) const;
        String GetCenter(uint32 start, uint32 stop) const;
        bool GetNextWord(String& word, int32& last_index) const;
        bool GetNextWord(String& word, int32& last_index, char token) const;
        bool GetNextWord(String& word, int32& last_index, const Vector<String> & token_array) const;
        uint32 GetOccurencesCount(char c) const;
        uint32 GetOccurencesCount(const String& word) const;
        uint32 Find(char c) const;
        uint32 FindLast(char c) const;
        uint32 Find(const String& word) const;
        int32 GetInteger() const;
        real GetReal() const;
        basic::String ToUpperCase() const;
        basic::String ToLowerCase() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Set(const char* text, ...);
        void SetLength(uint32 length);
        void SetEmpty();
        void Replace(const String& in, const String& out);
        void CutLeft(uint32 length);
        void CutRight(uint32 length);
        void Serialize(coffee::meta::Stream& stream);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        char* _Buffer;
        uint32 _Length;
        uint32 _ReservedSize;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, String);
}
}
#endif

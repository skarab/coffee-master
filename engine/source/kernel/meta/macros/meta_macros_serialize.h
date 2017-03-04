#ifndef _COFFEE_META_MACROS_SERIALIZE_H_
#define _COFFEE_META_MACROS_SERIALIZE_H_

//-DEFINES----------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
/// Serialize an object
//------------------------------------------------------------------------------------------------//
#define COFFEE_SerializeObject(_object_reference_) \
    stream.GetSerializer().SerializeObject(stream, _object_reference_); \

//------------------------------------------------------------------------------------------------//
/// Serialize a scalar, knowing its format
//------------------------------------------------------------------------------------------------//
#define COFFEE_SerializeScalarFormat(_scalar_address_, _scalar_format_) \
    { \
        COFFEE_Assert(_scalar_address_!=NULL, coffee::core::ERROR_CODE_IncorrectUsage, "Failed to serialize NULL scalar"); \
        ulong scalar_size = coffee::meta::SCALAR_FORMAT_GetFormatSize(_scalar_format_); \
        if (stream.GetMode()==coffee::storage::MODE_Output) \
        { \
            stream.GetStream().Push(_scalar_address_, scalar_size); \
        } \
        else \
        { \
            COFFEE_Copy(\
                _scalar_address_, \
                stream.GetStream().Pop(scalar_size), \
                scalar_size ); \
        } \
    } \

//------------------------------------------------------------------------------------------------//
/// Serialize a scalar
//------------------------------------------------------------------------------------------------//
#define COFFEE_SerializeScalar(_scalar_address_, _scalar_type_) \
    { \
        COFFEE_Assert(_scalar_address_!=NULL, coffee::core::ERROR_CODE_IncorrectUsage, "Failed to serialize NULL scalar"); \
        ulong scalar_size = coffee::meta::TYPE<_scalar_type_>().Get().GetSize(); \
        if (stream.GetMode()==coffee::storage::MODE_Output) \
        { \
            stream.GetStream().Push(_scalar_address_, scalar_size); \
        } \
        else \
        { \
            COFFEE_Copy(\
                _scalar_address_, \
                stream.GetStream().Pop(scalar_size), \
                scalar_size ); \
        } \
    } \

//------------------------------------------------------------------------------------------------//
/// Serialize a scalar array, knowing the scalar format
//------------------------------------------------------------------------------------------------//
#define COFFEE_SerializeScalarArrayFormat(_type_, _scalar_array_buffer_, _scalar_array_count_, _scalar_format_) \
    { \
        ulong scalar_size = coffee::meta::SCALAR_FORMAT_GetFormatSize(_scalar_format_); \
        COFFEE_SerializeScalar(&_scalar_array_count_, uint32); \
        if (stream.GetMode()==coffee::storage::MODE_Output) \
        { \
            stream.GetStream().Push((char*)_scalar_array_buffer_, scalar_size*((ulong)_scalar_array_count_)); \
        } \
        else \
        { \
            if (_scalar_array_count_==0) \
            { \
                if (_scalar_array_buffer_!=NULL) \
                { \
                    COFFEE_Free(_scalar_array_buffer_); \
                    _scalar_array_buffer_=NULL; \
                } \
            } \
            else \
            { \
                if (_scalar_array_buffer_==NULL) \
                    _scalar_array_buffer_ = (_type_ *) COFFEE_Allocate(scalar_size * ((ulong) _scalar_array_count_)); \
                else \
                    _scalar_array_buffer_ = (_type_ *) COFFEE_Reallocate(_scalar_array_buffer_, scalar_size * ((ulong) _scalar_array_count_)); \
                 \
                COFFEE_Copy(\
                    _scalar_array_buffer_, \
                    stream.GetStream().Pop(scalar_size * ((ulong) _scalar_array_count_)), \
                    scalar_size * ((ulong) _scalar_array_count_)); \
            } \
        } \
    } \

//------------------------------------------------------------------------------------------------//
/// Serialize a scalar array
//------------------------------------------------------------------------------------------------//
#define COFFEE_SerializeScalarArray(_type_, _scalar_array_buffer_, _scalar_array_count_) \
    { \
        ulong scalar_size = coffee::meta::TYPE<_type_>().Get().GetSize(); \
        COFFEE_SerializeScalar(&_scalar_array_count_, uint32); \
        if (stream.GetMode()==coffee::storage::MODE_Output) \
        { \
            stream.GetStream().Push((char*)_scalar_array_buffer_, scalar_size*((ulong)_scalar_array_count_)); \
        } \
        else \
        { \
            if (_scalar_array_count_==0) \
            { \
                if (_scalar_array_buffer_!=NULL) \
                { \
                    COFFEE_Free(_scalar_array_buffer_); \
                    _scalar_array_buffer_=NULL; \
                } \
            } \
            else \
            { \
                if (_scalar_array_buffer_==NULL) \
                    _scalar_array_buffer_ = (_type_ *) COFFEE_Allocate(scalar_size * ((ulong) _scalar_array_count_)); \
                else \
                    _scalar_array_buffer_ = (_type_ *) COFFEE_Reallocate(_scalar_array_buffer_, scalar_size * ((ulong) _scalar_array_count_)); \
                 \
                COFFEE_Copy(\
                    _scalar_array_buffer_, \
                    stream.GetStream().Pop(scalar_size * ((ulong) _scalar_array_count_)), \
                    scalar_size * ((ulong) _scalar_array_count_)); \
            } \
        } \
    } \

#endif

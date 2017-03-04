#ifndef _COFFEE_RESOURCE_MACROS_H_
#define _COFFEE_RESOURCE_MACROS_H_

//-DEFINES----------------------------------------------------------------------------------------//

#define COFFEE_Resource(_class_) \
    COFFEE_Type(_class_); \
    public: \
        _class_(const _class_& resource); \
        _class_(const coffee::resource::Object& resource); \
        _class_(coffee::resource::Chunk& resource_chunk); \
        _class_& operator =(const _class_& resource); \
        _class_& operator =(const coffee::resource::Object& resource); \
        _class_& operator =(coffee::resource::Chunk& resource_chunk); \
        static coffee::basic::String GetStaticResourceName(); \
        static coffee::basic::String GetStaticResourceType(); \
        virtual coffee::basic::String GetResourceName() const; \
        virtual coffee::basic::String GetResourceType() const; \
        virtual uint32 GetResourceModes() const; \

//------------------------------------------------------------------------------------------------//

#define COFFEE_BeginResource(_namespace_, _class_, _resource_name_, _resource_type_, _resource_modes_) \
    _namespace_::_class_::_class_(const _class_& resource) \
    { \
        ConstructInstance(); \
        coffee::resource::Object::operator =(resource); \
        coffee::resource::Object::_PostInstantiate(resource); \
    } \
    _namespace_::_class_::_class_(const coffee::resource::Object& resource) \
    { \
        ConstructInstance(); \
        coffee::resource::Object::operator =(resource); \
    } \
    _namespace_::_class_::_class_(coffee::resource::Chunk& resource_chunk) \
    { \
        ConstructInstance(); \
        coffee::resource::Object::operator =(resource_chunk); \
    } \
    _namespace_::_class_& _namespace_::_class_::operator =(const _class_& resource) \
    { \
        coffee::resource::Object::operator=(resource); \
        coffee::resource::Object::_PostInstantiate(resource); \
        return *this; \
    } \
    _namespace_::_class_& _namespace_::_class_::operator =(const coffee::resource::Object& resource) \
    { \
        coffee::resource::Object::operator=(resource); \
        return *this; \
    } \
    _namespace_::_class_& _namespace_::_class_::operator =(coffee::resource::Chunk& resource_chunk) \
    { \
        coffee::resource::Object::operator=(resource_chunk); \
        return *this; \
    } \
    coffee::basic::String _namespace_::_class_::GetStaticResourceName() \
    { \
        return coffee::basic::String(_resource_name_); \
    } \
    coffee::basic::String _namespace_::_class_::GetStaticResourceType() \
    { \
        return coffee::basic::String(_resource_type_); \
    } \
    coffee::basic::String _namespace_::_class_::GetResourceName() const \
    { \
        return GetStaticResourceName(); \
    } \
    coffee::basic::String _namespace_::_class_::GetResourceType() const \
    { \
        return GetStaticResourceType(); \
    } \
    uint32 _namespace_::_class_::GetResourceModes() const \
    { \
        return _resource_modes_; \
    } \
    COFFEE_BeginType(_namespace_::_class_); \

//------------------------------------------------------------------------------------------------//

#define COFFEE_EndResource() \
    COFFEE_EndType(); \

//------------------------------------------------------------------------------------------------//

#define COFFEE_ResourceProperty(_type_, _name_, _meta_mode_, _property_flags_) \
    type->AddAttribute(\
        #_name_ "Property", \
        "resource::PropertyBase", \
        (ulong_ptr) &temp_instance._name_ - (ulong_ptr) &temp_instance, \
        0, \
        COFFEE_New(coffee::meta::ParamProperty, \
            (((_property_flags_ & coffee::resource::PROPERTY_FLAG_Instantiable) > 0 \
            || (_property_flags_ & coffee::resource::PROPERTY_FLAG_LOD) > 0) \
            && ((_meta_mode_ & coffee::meta::MODE_Serializeable) > 0)) ? coffee::meta::MODE_Serializeable : 0, \
            _property_flags_) \
       ); \
    type->AddAttribute(\
        #_name_, \
        #_type_, \
        (ulong_ptr) &temp_instance._name_._metaValue() - (ulong_ptr) &temp_instance, \
        _meta_mode_ \
       ); \

//------------------------------------------------------------------------------------------------//

#define COFFEE_ResourcePropertyCustom(_type_, _name_, _param_, _property_flags_) \
    { \
        coffee::meta::Param * custom_param = _param_; \
        type->AddAttribute(\
             #_name_ "Property", \
            "resource::PropertyBase", \
            (ulong_ptr) &temp_instance._name_ - (ulong_ptr) &temp_instance, \
            0, \
            COFFEE_New(coffee::meta::ParamProperty, \
                (((_property_flags_ & coffee::resource::PROPERTY_FLAG_Instantiable) > 0 \
                || (_property_flags_ & coffee::resource::PROPERTY_FLAG_LOD) > 0) \
                && ((custom_param->GetMode() & coffee::meta::MODE_Serializeable) > 0)) ? coffee::meta::MODE_Serializeable : 0, \
                _property_flags_) \
           ); \
        type->AddAttribute(\
            #_name_, \
            #_type_, \
            (ulong_ptr) &temp_instance._name_._metaValue() - (ulong_ptr) &temp_instance, \
            0, \
            custom_param \
           ); \
    } \
 
//------------------------------------------------------------------------------------------------//

#define COFFEE_RegisterResourceLibrary(_resource_type_) \
    { \
        coffee::resource::Library* library = COFFEE_New(coffee::resource::Library, _resource_type_); \
        SendEvent(coffee::shell::Event(coffee::shell::EventCode(coffee::shell::MODULE_EVENT_Register, coffee::shell::Module::GetClassMetaType()), coffee::shell::EventParameters(NULL, library))); \
        coffee::resource::Manager::Get().RegisterLibrary(*library); \
    } \

#endif

#include "coffee.h"
#include "system/graphics/device/graphics_device.h"
#include "system/graphics/device/graphics_device_windows.hpp"

//-DEFINES----------------------------------------------------------------------------------------//

#define COFFEE_IsExtensionSupported(_extension_, _error_on_failure_) \
    (GLEE_##_extension_==GL_TRUE); \
    COFFEE_Log(core::Log::None, "Checking required extension %s", #_extension_); \
    if (_error_on_failure_ && !(GLEE_##_extension_==GL_TRUE)) \
    { \
        basic::String message(#_extension_); \
        message += " is unsupported"; \
        COFFEE_Error(core::ERROR_CODE_UnsupportedExtension, message.GetBuffer()); \
    } \

namespace coffee
{
namespace graphics
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Device);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Device::Device() :
        _ExtensionsString(NULL),
        _Window(NULL),
        _FrameWidth(0),
        _FrameHeight(0),
        _Width(0),
        _Height(0),
        _BitsPerPixel(0),
        _Frequency(0),
        _AspectRatio(0),
        _ItHasActiveContext(false),
        _OpenglContext(NULL),
        _ItIsVisible(true),
        _SupportedFeatures(0)
    {
        COFFEE_CreateSingleton(Device);
    }

    //--------------------------------------------------------------------------------------------//

    Device::~Device()
    {
        COFFEE_DestroySingleton(Device);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Device::CheckStatus() const
    {
        // Note: glGetError acts like glFlush and should be removed in release or player build...
        int32 error_code;
        if (GL_NO_ERROR==(error_code=glGetError()))
            return true;
        COFFEE_Warning(basic::String("Graphics error 0x%x (%s, %s, %s)", error_code,
            (char *) glGetString(GL_PROGRAM_ERROR_STRING_ARB),
            (char*)glGetString(GL_PROGRAM_ERROR_STRING_NV),
            GLeeGetErrorString()).GetBuffer());
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Device::Initialize()
    {
        _CreateWindow();
        _InitializeExtensions();
    }

    //--------------------------------------------------------------------------------------------//

    void Device::Finalize()
    {
        _DestroyWindow();
    }

    //--------------------------------------------------------------------------------------------//

    void Device::Update(bool it_is_visible)
    {
        _UpdateWindow(it_is_visible);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_InitializeExtensions()
    {
        if (GLeeInit())
        {
            COFFEE_Log(core::Log::FatalError, "GLeeInit failed: %s", GLeeGetErrorString());
            COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to initialize GLee");
        }

        _ExtensionsString = (char*)glGetString(GL_EXTENSIONS);
        char* version = (char*)glGetString(GL_VERSION);

        COFFEE_Log(core::Log::None, "OpenGL version : %s", version);

        if (version[0]=='0' || version[0]=='1')
            COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to find OpenGL v2.1 or greater");

        if (version[0]=='2' && version[2]=='0')
            COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to find OpenGL v2.1 or greater");

        // Shaders
        COFFEE_IsExtensionSupported(ARB_shading_language_100, true);
        COFFEE_IsExtensionSupported(ARB_vertex_program, true);
        COFFEE_IsExtensionSupported(ARB_vertex_shader, true);
        COFFEE_IsExtensionSupported(ARB_fragment_program, true);
        COFFEE_IsExtensionSupported(ARB_fragment_shader, true);
        COFFEE_IsExtensionSupported(ARB_shader_objects, true);
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_GeometryShader, GLEE_EXT_geometry_shader4==GL_TRUE);

        // Textures
        COFFEE_IsExtensionSupported(EXT_texture_sRGB, true);
        COFFEE_IsExtensionSupported(ARB_multitexture, true);
        COFFEE_IsExtensionSupported(ARB_texture_cube_map, true);
        COFFEE_IsExtensionSupported(EXT_texture_filter_anisotropic, true);
        COFFEE_IsExtensionSupported(ARB_texture_float, true);
        COFFEE_IsExtensionSupported(EXT_texture_array, true);
        COFFEE_IsExtensionSupported(EXT_texture3D, true);

        // Particles / effects
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_SubstractiveBlend, GLEE_EXT_blend_subtract==GL_TRUE);

        // Shadows
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_StencilWrap, GLEE_EXT_stencil_wrap==GL_TRUE);
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_TwoSidedStencil, GLEE_EXT_stencil_two_side==GL_TRUE);
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_TwoSidedStencilATI, GLEE_ATI_separate_stencil==GL_TRUE);
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_ShadowVolumes, IsSupporting(DEVICE_SUPPORT_GeometryShader));
        COFFEE_EnableFlag(_SupportedFeatures, DEVICE_SUPPORT_SoftShadows, (GLEE_ARB_stencil_texturing==GL_TRUE) && (GLEE_EXT_gpu_shader4));
        
        // FBO / VBO
        COFFEE_IsExtensionSupported(EXT_packed_float, true);
        COFFEE_IsExtensionSupported(EXT_packed_depth_stencil, true);
        COFFEE_IsExtensionSupported(ARB_vertex_buffer_object, true);
        COFFEE_IsExtensionSupported(EXT_framebuffer_object, true);
        COFFEE_IsExtensionSupported(EXT_framebuffer_blit, true);
        COFFEE_IsExtensionSupported(ARB_texture_rectangle, true);
        
        COFFEE_Log(core::Log::None, "Required graphics extensions checked!");
    
        // Anisotropic filtering
        int32 largest_supported_anisotropy;
        glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
        if (GetConfig().GetState(CONFIG_STATE_Anisotropic)>(uint32)largest_supported_anisotropy)
        {
            COFFEE_Log(core::Log::Warning, "Failed to set %ix anisotropic filtering", GetConfig().GetState(CONFIG_STATE_Anisotropic));
            GetConfig().SetState(CONFIG_STATE_Anisotropic, (uint32)largest_supported_anisotropy);
        }
        COFFEE_Log(core::Log::None, "Anisotropic filtering set to %ix", GetConfig().GetState(CONFIG_STATE_Anisotropic));

        int32 maximum_color_attachement;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &maximum_color_attachement);
        _MaximumFrameColorLayers = maximum_color_attachement;
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_EnableVerticalSync()
    {
        bool it_is_enabled = _Config.IsModeEnabled(CONFIG_MODE_VerticalSync);

        if (!GLEE_WGL_EXT_swap_control)
        {
            COFFEE_Log(core::Log::Warning, "failed to change vertical sync");
        }
        else
        {
            if (wglSwapIntervalEXT=(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT"))
            {
                wglSwapIntervalEXT(it_is_enabled);
                if (it_is_enabled) COFFEE_Log(core::Log::None, "VerticalSync is enabled");
                else COFFEE_Log(core::Log::None, "VerticalSync is disabled");
            }
            else
            {
                COFFEE_Log(core::Log::Warning, "failed to change vertical sync");
            }
        }
    }

}
}

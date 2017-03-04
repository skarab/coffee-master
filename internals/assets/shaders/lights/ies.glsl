// -------------------------------------------------------------------------------------------------
// IES light
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    uv = gl_MultiTexCoord0.xy;
    view_vector = gl_Color.xyz;
    vec4 pos = ftransform();
    pos.z = 0.999999;
    gl_Position = pos;
}

// -------------------------------------------------------------------------------------------------
// fragment_shader
// -------------------------------------------------------------------------------------------------
#version 130
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#include "../helpers.glslh"

uniform sampler2DRect depth_texture;
uniform sampler2DRect normal_texture;
uniform sampler2DRect base_texture;
uniform sampler2DRect material_texture;
uniform sampler2D ies_texture;
uniform sampler2DRect shadow_texture;
uniform vec4 light_position; 
uniform vec3 light_direction;
uniform vec4 light_color;
uniform float light_intensity;
uniform float light_apex;
uniform float light_radius;
uniform float light_softness;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    float depth = UnpackDepth(texture2DRect(depth_texture, uv).xy);
    vec3 normal = UnpackNormal(texture2DRect(normal_texture, uv).xyz);
    vec3 position = view_vector*depth;
    
    vec3 pixel_light_direction = light_position.xyz-position;
    float distance = length(pixel_light_direction);    
    pixel_light_direction = normalize(pixel_light_direction);

    // Compute BRDF
    #include "prepare_brdf.glslh"
    #include "brdf_diffuse_ashikhmin.glslh"
    #include "brdf_specular_schlick.glslh"

    // Compute Illumination (Lux) from Intensity (Candela)
    float cosinus = dot(pixel_light_direction, light_direction);
    vec2 ies_position;
    ies_position.x = sqrt(1.0-cosinus*cosinus)*distance/(light_radius*light_apex*2.0);
    ies_position.y = distance*cosinus/light_radius;
    float illumination = light_intensity*texture2D(ies_texture, ies_position*0.5+0.5).x;
    
    color *= light_color.xyz*illumination;
    
    #ifdef GL_EXT_gpu_shader4
        gl_FragColor = vec4(ApplyShadows(color, shadow_texture, light_softness, uv), 1.0);
    #else
        gl_FragColor = vec4(color, 1.0);
    #endif
}

// -------------------------------------------------------------------------------------------------
// Ambient
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

uniform mat4 world_to_camera_matrix;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    uv = gl_MultiTexCoord0.xy;
    view_vector = (vec4(gl_Color.xyz, 0.0)*world_to_camera_matrix).xyz;
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
#include "helpers.glslh"

uniform sampler2DRect normal_texture;
uniform sampler2DRect base_texture;
uniform sampler2DRect material_texture;
uniform sampler2D ambient_texture_lod0;
uniform sampler2D ambient_texture_lod1;
uniform sampler2D ambient_texture_lod2;
uniform sampler2D ambient_texture_lod3;

uniform mat4 world_to_camera_matrix2;
uniform float sky_intensity;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    vec3 albedo = texture2DRect(base_texture, uv).xyz;
    vec2 material = texture2DRect(material_texture, uv).xy;
    vec3 normal = UnpackNormal(texture2DRect(normal_texture, uv).xyz);
    normal = (vec4(normal, 0.0)*world_to_camera_matrix2).xyz;
    normal = reflect(normalize(view_vector), normal);
    
    vec2 sky_uv;
    sky_uv.x = 1.0+atan(normal.x, -normal.z)/2.0/3.14159;
    sky_uv.y = acos(normal.y)/3.14159;
    
    vec3 rgbe0 = RGBE(texture2D(ambient_texture_lod0, sky_uv)); // 0.0
    vec3 rgbe1 = RGBE(texture2D(ambient_texture_lod1, sky_uv)); // 0.33
    vec3 rgbe2 = RGBE(texture2D(ambient_texture_lod2, sky_uv)); // 0.66
    vec3 rgbe3 = RGBE(texture2D(ambient_texture_lod3, sky_uv)); // 1.0
    
    float s = clamp(material.y*1.2, 0.0, 1.0);
    vec3 s1 = mix(rgbe0, rgbe1, s/0.33)*(1.0-step(0.33, s));
    vec3 s2 = mix(rgbe1, rgbe2, (s-0.33)/0.33)*(1.0-step(0.66, s))*step(0.33, s);
    vec3 s3 = mix(rgbe2, rgbe3, (s-0.66)/0.33)*step(0.66, s);
    vec3 ambient = (s1+s2+s3)*sky_intensity*material.x*albedo*4.0;
    
    gl_FragColor = vec4(ambient, 1.0);
}

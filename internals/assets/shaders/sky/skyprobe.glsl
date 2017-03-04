// -------------------------------------------------------------------------------------------------
// Render sky probe
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
#include "../helpers.glslh"

uniform sampler2D sky_texture;
uniform float sky_intensity;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    vec3 world_direction = normalize(view_vector);
    
    vec2 sky_uv;
    sky_uv.x = 1.0+atan(world_direction.x, -world_direction.z)/2.0/3.14159;
    sky_uv.y = acos(world_direction.y)/3.14159;
    
    vec3 sky_color = RGBE(texture2D(sky_texture, sky_uv)) * sky_intensity;
    
    gl_FragColor = vec4(sky_color, 1.0);
}

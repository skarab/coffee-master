// -------------------------------------------------------------------------------------------------
// Debugger: display infinite/nan values as white, others as black
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 120

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    uv = gl_MultiTexCoord0.xy;
    view_vector = gl_Color.xyz;
    gl_Position = ftransform();
}

// -------------------------------------------------------------------------------------------------
// fragment_shader
// -------------------------------------------------------------------------------------------------
#version 130
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#include "../../shaders/helpers.glslh"

uniform sampler2DRect input_texture;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    vec3 values = texture2DRect(input_texture, uv).xyz;
    vec3 color = vec3(0.0);
    if (isnan(values.r) || isinf(values.r))
        color.r = 1.0;
    if (isnan(values.g) || isinf(values.g))
        color.g = 1.0;
    if (isnan(values.b) || isinf(values.b))
        color.b = 1.0;    
    gl_FragColor = vec4(color, 1.0);
}

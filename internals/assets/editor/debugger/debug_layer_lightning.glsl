// -------------------------------------------------------------------------------------------------
// Debugger: display Lightning HDR layer
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
#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#include "../../shaders/helpers.glslh"

uniform sampler2DRect input_texture;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    vec3 color = texture2DRect(input_texture, uv).xyz;
    
    // hardcoded exposure based on sun luminance
    color /= 40000.0;
    
    gl_FragColor = vec4(color, 1.0);
}

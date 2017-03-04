// -------------------------------------------------------------------------------------------------
// Debugger: display Depth layer
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
uniform float near_clip;
uniform float far_clip;

varying vec2 uv;
varying vec3 view_vector;

void main()
{
    float depth = texture2DRect(input_texture, uv).x;
    float n = 2.0*depth-1.0;
    depth = 2.0*near_clip*far_clip/(far_clip+near_clip-n*(far_clip-near_clip));
    
    // use same method as linear depth
    depth -= near_clip;
    depth /= far_clip-near_clip;
    depth *= 60.0;
    depth = 1.0-depth;
    
    gl_FragColor = vec4(depth, depth, depth, 1.0);
}

// -------------------------------------------------------------------------------------------------
// Generate mipmaps using simple blur
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#version 140
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect input_texture;

varying vec2 uv;

void main()
{
    vec3 blur = (texture2DRect(input_texture, uv+vec2(-1.0, -1.0)).xyz
        + texture2DRect(input_texture, uv+vec2(-1.0, 1.0)).xyz
        + texture2DRect(input_texture, uv+vec2(1.0, 1.0)).xyz
        + texture2DRect(input_texture, uv+vec2(1.0, -1.0)).xyz)/4.0;
        
    gl_FragColor = vec4(blur, 0.0);
}

// -------------------------------------------------------------------------------------------------
// Compute average scene luminance (result is built using mipmaps generation)
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
    vec3 illumination = texture2DRect(input_texture, uv).xyz;
    float luminance = illumination.x*0.299 + illumination.y*0.587 + illumination.z*0.114;
    if (isnan(luminance) || isinf(luminance))
        luminance = 0.0;
    gl_FragColor = vec4(luminance, 0.0, 0.0, 0.0);
}

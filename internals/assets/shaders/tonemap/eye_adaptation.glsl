// -------------------------------------------------------------------------------------------------
// Blend old & new luminances depending of eye parameters
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#version 130

uniform sampler2D old_texture;
uniform sampler2D new_texture;
uniform float eye_bright_adaptation;
uniform float eye_dark_adaptation;
uniform float eye_adaptation_time;

varying vec2 uv;

void main()
{
    float old_luminance = texture2D(old_texture, vec2(0.5, 0.5)).x;
    float new_luminance = texture2D(new_texture, vec2(0.5, 0.5)).x;
    float bright = clamp((new_luminance-old_luminance)*1000.0, 0.0, 1.0);
    float luminance = mix(old_luminance, new_luminance,
        eye_adaptation_time/(bright*eye_bright_adaptation
        +(1.0-bright)*eye_dark_adaptation));
    gl_FragColor = vec4(luminance, 0.0, 0.0, 0.0);
}

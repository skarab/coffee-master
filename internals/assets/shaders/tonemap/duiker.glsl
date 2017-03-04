// -------------------------------------------------------------------------------------------------
// Haarm-Peter Duiker’s curve Tone Mapper
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#include "tonemapper_fragment_begin.glslh"

uniform sampler2D lut;


vec3 log10(vec3 v)
{
    return log2(v)/log2(10);
}

void main()
{
    vec3 color = texture2DRect(input_texture, uv).xyz;
    
    color *= GetExposure();
    vec3 ld = vec3(0.002, 0.002, 0.002);
    float linReference = 0.18;
    float logReference = 444.0;
    float logGamma = 0.45;
    vec3 LogColor;
    
    LogColor.rgb = (log10(color.rgb*0.4/linReference)/ld*logGamma+logReference)/1023.f;
    LogColor.rgb = clamp(LogColor.rgb, 0.0, 1.0);
    float FilmLutWidth = 256;
    float Padding = 0.5/FilmLutWidth;

    // Apply response lookup and color grading for target display
    color.r = texture2D(lut, vec2(mix(Padding,1-Padding,LogColor.r), 0.5)).r;
    color.g = texture2D(lut, vec2(mix(Padding,1-Padding,LogColor.g), 0.5)).r;
    color.b = texture2D(lut, vec2(mix(Padding,1-Padding,LogColor.b), 0.5)).r;

    gl_FragColor = vec4(color, 1.0);
}


// -------------------------------------------------------------------------------------------------
// Uncharted 2 Tone Mapper
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#include "tonemapper_fragment_begin.glslh"


vec3 ApplyTonemap(vec3 v)
{
    float A = 0.15;
    float B = 0.50;
    float C = 0.10;
    float D = 0.20;
    float E = 0.02;
    float F = 0.30;

    return ((v*(A*v+C*B)+D*E)/(v*(A*v+B)+D*F))-E/F;
}

#include "tonemapper_fragment_end.glslh"

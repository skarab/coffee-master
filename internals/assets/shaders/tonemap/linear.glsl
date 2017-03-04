// -------------------------------------------------------------------------------------------------
// Linear Tone Mapper
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#include "tonemapper_fragment_begin.glslh"


vec3 ApplyTonemap(vec3 v)
{
    return v*GetExposure();
}

#include "tonemapper_fragment_end.glslh"

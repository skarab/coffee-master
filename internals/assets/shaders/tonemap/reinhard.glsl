// -------------------------------------------------------------------------------------------------
// Reinhard Tone Mapper
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#include "tonemapper_fragment_begin.glslh"


vec3 ApplyTonemap(vec3 v)
{
    v *= GetExposure();
    return v/(v+1.0);
}

#include "tonemapper_fragment_end.glslh"

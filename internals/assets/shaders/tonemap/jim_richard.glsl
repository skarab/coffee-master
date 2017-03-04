// -------------------------------------------------------------------------------------------------
// Jim Hejl and Richard Burgess-Dawson Tone Mapper
// -------------------------------------------------------------------------------------------------

// vertex_shader
#include "tonemapper_vertex.glslh"

// fragment_shader
#include "tonemapper_fragment_begin.glslh"


vec3 ApplyTonemap(vec3 v)
{
    v *= GetExposure();
    v.x = max(0, v.x-0.004);
    v.y = max(0, v.y-0.004);
    v.z = max(0, v.z-0.004);
    return (v*(v*6.2+0.5))/(v*(v*6.2+1.7)+0.06);
}

#include "tonemapper_fragment_end.glslh"

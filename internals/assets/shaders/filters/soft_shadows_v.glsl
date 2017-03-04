// -------------------------------------------------------------------------------------------------
// Fake soft shadows filter - vertical pass
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

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
#version 130
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#include "../helpers.glslh"

uniform sampler2DRect depth_texture;
uniform sampler2DRect normal_texture;
uniform vec4 light_position;
uniform float light_softness;
uniform vec2 frame_size;

varying vec2 uv;
varying vec3 view_vector;

#ifdef GL_EXT_gpu_shader4
    uniform sampler2DRect shadow_texture;
    
    float ComputeSoftShadows(float distance, float depth, vec3 normal)
    {
        float radius = distance*distance*light_softness/(frame_size.y*depth/6.0);
        
        float stencil = 0.01;
        float count = stencil;
        for (float i=-4.0 ; i<=4.0 ; i+=0.5)
        {
            vec2 t = vec2(uv.x, uv.y+i*radius);
            vec3 n = UnpackNormal(texture2DRect(normal_texture, t).xyz);
            float coef = (5.0-abs(i))*float(dot(n, normal)>0.9);
            stencil += coef*texture2DRect(shadow_texture, t).x;
            count += coef;
        }
        return stencil/count;
    }
#endif

void main()
{    
    float depth = UnpackDepth(texture2DRect(depth_texture, uv).xy);
    vec3 normal = UnpackNormal(texture2DRect(normal_texture, uv).xyz);
    vec3 position = view_vector*depth;
    float distance = (1.0-light_position.w)*10.0+light_position.w*length(light_position.xyz-position);
    
    #ifdef GL_EXT_gpu_shader4
        gl_FragColor = vec4(ComputeSoftShadows(distance, position.z, normal), 0.0, 0.0, 1.0);
    #else
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    #endif
}

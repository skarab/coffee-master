// -------------------------------------------------------------------------------------------------
// Point cloud test
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

uniform mat4 camera_to_local_matrix;

varying vec3 uv;
varying float depth;
varying mat3 normal_matrix;

void main()
{
    mat4 t;
    t[0] = camera_to_local_matrix[0];
    t[1] = camera_to_local_matrix[1];
    t[2] = camera_to_local_matrix[2];
    t[3] = vec4(0.0, 0.0, 0.0, 1.0);
    
    normal_matrix[0] = gl_ModelViewMatrix[0].xyz;
    normal_matrix[1] = gl_ModelViewMatrix[1].xyz;
    normal_matrix[2] = gl_ModelViewMatrix[2].xyz;
    
    uv = (t*gl_Vertex).xyz+0.5;
    
    vec4 position = gl_ModelViewMatrix*t*gl_Vertex;
    depth = position.z;
    gl_Position = gl_ProjectionMatrix*position;
}

// -------------------------------------------------------------------------------------------------
// fragment_shader
// -------------------------------------------------------------------------------------------------
#version 130
#extension GL_ARB_texture_rectangle : enable
#include "helpers.glslh"

uniform sampler3D base_texture;
uniform sampler3D normal_texture;

varying vec3 uv;
varying float depth;
varying mat3 normal_matrix;

void main()
{
    vec4 c = texture3D(base_texture, uv);
    if (c.a<0.5) discard;
    
    // Write packed linear depth
    gl_FragData[0].xy = PackDepth(depth);    
    
    // Write normal layer
    vec3 normal = texture3D(normal_texture, uv).xyz*2.0-1.0;
    //normal.xy = -normal.xy;
    normal = normalize(normal_matrix*normal);
    gl_FragData[1].xyz = PackNormal(normal);
     
    // Write color layer
    gl_FragData[2].xyz = c.xyz*200.0+100.0;
    
    // Write material layer
    gl_FragData[3].x = 0.1;
    gl_FragData[3].y = 0.7;
}

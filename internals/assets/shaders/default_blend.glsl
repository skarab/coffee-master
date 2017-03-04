// -------------------------------------------------------------------------------------------------
// Default shader using alpha blend
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

uniform mat4 camera_to_local_matrix;

varying vec2 uv;
varying vec3 eye_vector;


void main()
{
    uv = gl_MultiTexCoord0.xy;

    mat3 tbn_matrix;
    tbn_matrix[0] = gl_MultiTexCoord1.xyz;
    tbn_matrix[1] = gl_MultiTexCoord2.xyz;
    tbn_matrix[2] = gl_Normal.xyz;

    eye_vector = (gl_Vertex.xyz-camera_to_local_matrix[3].xyz) * tbn_matrix;

    gl_Position = ftransform();
}

// -------------------------------------------------------------------------------------------------
// fragment_shader
// -------------------------------------------------------------------------------------------------
#version 130
#extension GL_ARB_texture_rectangle : enable
#include "helpers.glslh"

uniform sampler2D base_texture;
uniform sampler2D height_texture;
uniform vec4 albedo;
uniform float height;

varying vec2 uv;
varying vec3 eye_vector;

void main()
{
    vec2 parallax_uv = ComputeParallax(uv, eye_vector, texture2D(height_texture, uv).x, height);
    gl_FragColor = vec4(texture2D(base_texture, parallax_uv).xyz, 1.0)*albedo;    
}

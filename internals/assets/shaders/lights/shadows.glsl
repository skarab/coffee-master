// -------------------------------------------------------------------------------------------------
// Shadow volumes
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

void main()
{
    gl_Position = gl_ModelViewMatrix*gl_Vertex;
}

// -------------------------------------------------------------------------------------------------
// geometry_shader
// -------------------------------------------------------------------------------------------------
#version 130
#extension GL_EXT_geometry_shader4: enable

uniform vec4 light_position; 
uniform int depth_pass;

void main()
{
    vec3 ns[3];     // Normals  
    vec3 d[3];      // Directions toward light  
     
    // Compute normal at each vertex.  
    ns[0] = cross(gl_PositionIn[2].xyz-gl_PositionIn[0].xyz,  
        gl_PositionIn[4].xyz-gl_PositionIn[0].xyz);  
    ns[1] = cross(gl_PositionIn[4].xyz-gl_PositionIn[2].xyz,  
        gl_PositionIn[0].xyz-gl_PositionIn[2].xyz);  
    ns[2] = cross(gl_PositionIn[0].xyz-gl_PositionIn[4].xyz,  
        gl_PositionIn[2].xyz-gl_PositionIn[4].xyz);
     
    // Compute direction from vertices to light.  
    d[0] = light_position.xyz-light_position.w*gl_PositionIn[0].xyz;  
    d[1] = light_position.xyz-light_position.w*gl_PositionIn[2].xyz;  
    d[2] = light_position.xyz-light_position.w*gl_PositionIn[4].xyz;  

    // Check if the main triangle faces the light.  
    if (!(dot(ns[0],d[0])>0 || dot(ns[1],d[1])>0 || dot(ns[2],d[2])>0))
        return;
    
    // Render caps if z-fail mode.  
    if (depth_pass==0)
    {  
        // Near cap
        gl_Position = gl_ProjectionMatrix*gl_PositionIn[0];
        EmitVertex();
        gl_Position = gl_ProjectionMatrix*gl_PositionIn[2];
        EmitVertex();
        gl_Position = gl_ProjectionMatrix*gl_PositionIn[4];
        EmitVertex();
        EndPrimitive();
        
        // Far cap 
        gl_Position = gl_ProjectionMatrix*vec4(light_position.w*gl_PositionIn[0].xyz-light_position.xyz,0);
        EmitVertex();
        gl_Position = gl_ProjectionMatrix*vec4(light_position.w*gl_PositionIn[4].xyz-light_position.xyz,0);
        EmitVertex();
        gl_Position = gl_ProjectionMatrix*vec4(light_position.w*gl_PositionIn[2].xyz-light_position.xyz,0);
        EmitVertex();
        EndPrimitive();  
    }
  
    // Loop over all edges and extrude if needed.  
   for (int i=0; i<3; i++)
   {  
        // Compute indices of neighbor triangle.  
        int v0 = i*2;  
        int nb = (i*2+1);  
        int v1 = (i*2+2) % 6;
        
        // Compute normals at vertices, the *exact* same way as done above!  
        ns[0] = cross(  
            gl_PositionIn[nb].xyz-gl_PositionIn[v0].xyz,  
            gl_PositionIn[v1].xyz-gl_PositionIn[v0].xyz);  
        ns[1] = cross(  
            gl_PositionIn[v1].xyz-gl_PositionIn[nb].xyz,  
            gl_PositionIn[v0].xyz-gl_PositionIn[nb].xyz);  
        ns[2] = cross(  
            gl_PositionIn[v0].xyz-gl_PositionIn[v1].xyz,  
            gl_PositionIn[nb].xyz-gl_PositionIn[v1].xyz);  
        
        // Compute direction to light, again as above.  
        d[0] = light_position.xyz-light_position.w*gl_PositionIn[v0].xyz;  
        d[1] = light_position.xyz-light_position.w*gl_PositionIn[nb].xyz;  
        d[2] = light_position.xyz-light_position.w*gl_PositionIn[v1].xyz;  

        // Extrude the edge if it does not have a neighbor, or if it's a possible silhouette.  
        if (gl_PositionIn[nb].w<1e-3 ||  
            (!(dot(ns[0],d[0])>0 || dot(ns[1],d[1])>0 || dot(ns[2],d[2])>0)))
        {  
            // Emit a quad as a triangle strip.  
            gl_Position = gl_ProjectionMatrix*gl_PositionIn[v0];
            EmitVertex();
            gl_Position = gl_ProjectionMatrix*vec4(light_position.w*gl_PositionIn[v0].xyz - light_position.xyz, 0);
            EmitVertex();
            gl_Position = gl_ProjectionMatrix*gl_PositionIn[v1];
            EmitVertex();
            gl_Position = gl_ProjectionMatrix*vec4(light_position.w*gl_PositionIn[v1].xyz - light_position.xyz, 0);
            EmitVertex();       
            EndPrimitive();  
        }  
    }  
}

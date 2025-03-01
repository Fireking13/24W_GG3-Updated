$input v_texcoord0, v_WorldSpacePos, v_normal 

uniform vec4 u_LightColour;
uniform vec4 u_LightPos;
uniform vec4 u_LightRange;

uniform vec4 u_LightAmbientPer;
uniform vec4 u_LightFalloff;
uniform mat4 u_MatWorldRotation;

#include <bgfx_shader.sh>

SAMPLER2D( u_TextureColor, 0 );

void main()
{
    vec3 rotatedNormal = mul( u_MatWorldRotation, vec4(v_normal,0) ).xyz;  

    vec3 LightPos = u_LightPos.xyz;
    vec3 LightColor = u_LightColour.xyz;
    float LightRange = u_LightRange.x;

    vec4 color = texture2D( u_TextureColor, v_texcoord0 );

    vec3 MaterialColour = color.rgb;

    vec3 Normal =  vec3(rotatedNormal.xyz);

    float DistionsFromLight = length(LightPos - v_WorldSpacePos);
    float FallOff = max(1 - (DistionsFromLight / LightRange)* u_LightFalloff.x, 0);

    vec3 DirToLight = normalize(LightPos - v_WorldSpacePos);

    float DiffusePercent = max(dot(Normal, DirToLight), 0);
    
    gl_FragColor = vec4(MaterialColour * LightColor * DiffusePercent * (1 - u_LightAmbientPer.x) * FallOff, 1);

    //gl_FragColor = vec4(Normal, 1);
}

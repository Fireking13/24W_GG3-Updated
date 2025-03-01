$input a_position,a_texcoord0, a_color0, a_normal
$output v_texcoord0, v_WorldSpacePos, v_normal, v_color0


#include <bgfx_shader.sh>

uniform mat4 u_MatWorld;
uniform mat4 u_MatView;
uniform mat4 u_MatProj;
uniform vec4 u_UVScale;
uniform vec4 u_UVOffset;


void main()
{
	vec4 objectSpacePosition = vec4(a_position, 1 );

    float colourAmount = (-objectSpacePosition.z / 5.0f);

    vec4 worldSpacePosition = mul(u_MatWorld, objectSpacePosition);
    vec4 viewSpacePosition = mul(u_MatView, worldSpacePosition);
    vec4 clipSpacePosition = mul(u_MatProj, viewSpacePosition);
    gl_Position = clipSpacePosition;

    v_WorldSpacePos = vec3(worldSpacePosition.x, worldSpacePosition.y, worldSpacePosition.z);

    if (objectSpacePosition.y < 0.29f)
    {
        v_color0 = vec4(150.0f / 255.0f, 75.0f / 255.0f, 0.0f, 1.0f);
    }
    else if (objectSpacePosition.y >= 0.29f)
    {
        v_color0 = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }

    v_normal = a_normal;
}

$input a_position,a_texcoord0, a_color0
$output v_texcoord0, v_color0


#include <bgfx_shader.sh>

uniform mat4 u_MatWorld;
uniform mat4 u_MatView;
uniform mat4 u_MatProj;
uniform vec4 u_UVScale;
uniform vec4 u_UVOffset;

void main()
{
	vec4 objectSpacePosition = vec4(a_position, 1 );

    float colourAmount = (objectSpacePosition.y / 5.0f);

    vec4 worldSpacePosition = mul(u_MatWorld, objectSpacePosition);
    vec4 viewSpacePosition = mul(u_MatView, worldSpacePosition);
    vec4 clipSpacePosition = mul(u_MatProj, viewSpacePosition);
    gl_Position = clipSpacePosition;

    v_color0 = vec4(colourAmount, colourAmount, colourAmount, 1.0);
    v_texcoord0 = a_texcoord0 * u_UVScale.xy + u_UVOffset.xy;
}

$input a_position, a_texcoord0
$output v_texcoord0

#include <bgfx_shader.sh>

uniform mat4 u_MatWorld;
uniform mat4 u_MatView;
uniform mat4 u_MatProj;
uniform vec4 u_UVScale;
uniform vec4 u_UVOffset;
uniform vec4 u_Time;

void main()
{
	vec4 objectSpacePosition = vec4(a_position, 1 );
    objectSpacePosition.y += sin( objectSpacePosition.x + u_Time.x )* 0.1f;
    vec4 worldSpacePosition = mul(u_MatWorld, objectSpacePosition);
    vec4 viewSpacePosition = mul(u_MatView, worldSpacePosition);
    vec4 clipSpacePosition = mul(u_MatProj, viewSpacePosition);
    gl_Position = clipSpacePosition;

	v_texcoord0 = a_texcoord0 * u_UVScale.xy + u_UVOffset.xy;
}

$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D( u_TextureColor, 0 );

void main()
{
    vec4 color = texture2D( u_TextureColor, v_texcoord0 );
    gl_FragColor = vec4(color.x - 1.0f + v_color0.x, color.y - 1.0f + v_color0.y, color.z - 1.0f + v_color0.z, 1.0f);
}

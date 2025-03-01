
see [Shaders](Shaders.md)
see [GLSL](GLSL.md)

Reminder: [Clip Space](Clip%20Space.md)

# Vertex Shader

The vertex shader is responsible for calculating the final location of the vertex in clip space.

- The final clip space location must be stored in **gl_Position** (a vec4)
- Can also calculate other values, which would get output as varyings
- Written in GLSL (or HLSL if using DirectX)

# Vertex Shader Inputs

- **Attributes**: These are stored in a VBO
	- See [Vertex Attributes and VBOs](Vertex%20Attributes%20and%20VBOs.md)
	- An array for the properties of the vertices, commonly:
		- Position
		- Color
		- Normals
		- Texture/UV coordinates
		- etc...
- **Uniforms**: user defined, commonly:
	- Object transform info
	- Camera transform info
	- Projection transform info
	- Time
	- Color, etc...

# Default Vertex Shader

The simplest vertex shader takes the position attribute from your VBO and sets the final position with that value.

```glsl
attribute vec2 a_Position;

void main()
{
	gl_Position = vec4( a_Position, 0, 1 );
}
```

For this to work, you'd have to plot points in [Clip Space](Clip%20Space.md) and just output them exactly how you plotted them.

# Uniforms

With uniforms you can pass in new values and use them to move vertices around.

```glsl
attribute vec2 a_Position;
uniform vec2 u_Offset;

void main()
{
    vec2 pos = a_Position + u_Offset;
	gl_Position = vec4( pos, 0, 1 );
}
```

Uniforms can be used to apply any transformation to your points, whether it's scale, rotation or translation. The example above would let us translate our shape to any position we want.

See [Uniforms](Uniforms.md) for more detail.
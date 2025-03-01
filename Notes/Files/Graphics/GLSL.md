
# OpenGL Shader Language (GLSL)

Shader programs are written in a language of their own.

In the case of OpenGL shaders, the language used is GLSL. DirectX uses another similar language called HLSL (High level shader language).

This language is very similar to C/C++.

# GLSL Data Types

GLSL supports the following data types natively:
- bool
- **float, vec2, vec3, vec4**         <- These are the most commonly used
- int, ivec2, ivec3, ivec4
- uint, uvec2, uvec3, uvec4
- mat2, mat3, **mat4**                 <- Along with this one
- more...

# GLSL Vector access: Swizzling

Unlike C++, GLSL has a great feature to access individual components from their vec2, vec3 and vec4 types called Swizzling

Here are some examples:
```glsl
vec4 color( 1.0f, 1.0f, 1.0f, 1.0f );

float red = color[0];
float green = color.g;
float blue = color.z;
float alpha = color.w;

vec3 RGB = color.rgb;
vec4 RGBA = color.xyzw;
vec4 ARGB = color.argb;
vec4 RRRR = color.rrrr;
```

# GLSL Vector Conversions

In GLSL, vectors can be converted to other vectors as follows:
```glsl
vec2 position2D( 5.0f, 10.0f );
vec3 position3D = vec3( position2D, 0.0f );
vec4 someNonsense = vec4( 0.0f, position2D, 1.0f );

gl_Position = vec4( position2D, 0.0f, 1.0f );
```

Basically if you want to make a vec4 type, you can supply any combination of the smaller types (3 floats, 2 vec2, a vec3 and a float in any order, etc).

# GLSL: Language Features

GLSL support many of the same language features and syntax as C/C++ including:
- structs
- for/while loops
- if/else, switch/case conditions
- arrays
- preprocessor defines and ifs
- functions

# GLSL: Language Feature Differences

There are many differences, such as:
- No includes
- No common libraries, like stl
- No support for recursive functions
- No support for pointers
- Function parameters can be given qualifiers
	- void someFunction(in float value1, out float value2, inout float value3)
- Floating point numbers shouldn't end with an 'f'... i.e. use 3.14 not 3.14f
- No support for goto

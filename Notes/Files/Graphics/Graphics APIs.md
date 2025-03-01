
# Description

Your game needs to be able to control the video card. Starting with copying resources like meshes, textures, and animations over to video memory. Then, each frame, giving instructions to the video card about what to draw, where to place objects, what texture to place on which objects, etc.

This all happens through an Application Programming Interface (API), which is a name for the set of functions that let you use a certain library or collection of code.

# Available Libraries

- **OpenGL 4** - available on just about every platform
- **Vulkan** (really just OpenGL 5) - available on most modern platforms
- **DirectX 11** - available on Windows and Xbox
- **DirectX 12** - available on Windows and Xbox
- **Metal** - available on OSX and iOS

These libraries have an associated low-level video card driver that they communicate with.

- The game code interfaces with the library
- That library communicates with the driver
- The driver sends commands to the video card

#### The Main Differences

OpenGL and DirectX 11 are higher level APIs and do a lot of work for you. For this reason they can be less efficient that newer APIs like DirectX 12, Vulkan and Metal, but they are a lot easier to program with.

The older APIs like OpenGL and DX11 are also quite synchronous, i.e. operations happen in a fixed order and instructions are generated on a single CPU thread. With GPUs becoming bigger and harder to keep busy, the newer APIs give programmers more tools to keep modern GPUs busy.

# Obsolete?

- **OpenGL 1 Immediate mode**
	- If you're searching online and find reference to functions like:
		- glBegin
		- glVertex
		- glEnd
		- glMatrixMode
		- etc
	- This is old legacy OpenGL 1.1 or OpenGL ES 1 code and shouldn't be used

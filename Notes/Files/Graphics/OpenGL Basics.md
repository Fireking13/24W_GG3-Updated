
# OpenGL Rendering Context

The rendering context is an object that holds the entire state of the graphics system for our application. This includes things like the main framebuffers, which textures are loaded, the state of shaders and their uniforms and attributes, the color the screen will clear to, and a ton more.

It's possible to create multiple contexts per application, for example if you want to open multiple windows, but generally for games we don't need this feature.

# Framebuffers

In order to draw anything to the screen, we need a framebuffer. This is essentially a large block of memory on the video card that stores the colors for each pixel on screen.

When creating the OpenGL context, we can set the format of the pixels in the framebuffer, usually simply set to 32bit color (8 bits for each of the red, green, and blue channels), but this would need to be higher for HDR (high dynamic range) rendering.

We also create a 2nd buffer for the depth values for each pixel. This is used in both 2d and 3d rendering for efficiency and to avoid sorting objects at times. More on this later.

# Double Buffering

We don't just create a single buffer for the pixels, we create two. One is actively being displayed on your screen, while the 2nd on is being drawn. We call these the Front buffer and the Back buffer.

Having 2 buffers prevents us from seeing partially draw scenes as they are being built.

# Swapping Buffers

```c++
SwapBuffers( deviceContext );
```

This is a Windows specific call, other operating systems will switch which frame buffer is visible in their own way.

By default, after calling this function, Windows will wait until the previous buffer has finished being presented. Then it will swap the 2 and start presenting the new screen.

This can be customized with a call to:

```c++
wglSwapInterval( 0 ); // Swap as fast as possible, might cause screen tearing.

wglSwapInterval( 1 ); // Wait for previous frame to finish displaying, will limit fps
					  //    to your monitor refresh rate.
```

Again, this is a Windows specific call, other platforms will be slightly different.

# Clearing the Screen

#### Choose a color to clear to

```c++
glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
```

The arguments are red, green, blue, alpha in a 0-1 range.
Alpha is for transparency, which isn't generally useful for the main screen buffers, but since clearing a texture would use the same function, it has a purpose.

#### Clear the screen

```c++
glClear( GL_COLOR_BUFFER_BIT );
```

The arguments are bit flags, if you don't know how bitflags work, it's not important for this function right now, but we'll discuss these later on.

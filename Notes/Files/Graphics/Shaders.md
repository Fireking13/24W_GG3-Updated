
# What is a Shader?
  
The word **Shader** is often used to refer to 2 different things:

- A hardware shader unit
	- A small processor on your video card
- The software shader program that runs on the hardware shader unit
	- A piece of software written in a custom language that resembles C

# Shader Units

Modern video cards have many hardware shader units (aka cores). Each is a separate processor that runs code on data and returns results.

Having 2000 shader units means the card can process 2000 vertex or fragment shader programs simultaneously.

Here's an idea of how many cores a variety of GPUs has:

|Video Card|Intel HD 4000|UHD Graphics 770 Mobile|Nvidia GTX 980|Nvidia GTX 1080|Nvidia RTX 2080|Radeon RX Vega 64|
|---|---|---|---|---|---|---|
|Shader Units|16|256|2048|2560|2944|4096|

|Video Card|Nvidia RTX 3060|Nvidia GTX 3080|Nvidia GTX 3090Ti|Nvidia RTX 4080|Nvidia RTX 4090Ti|Radeon Instinct MI300|
|---|---|---|---|---|---|---|
|Shader Units|3584|8704|10752|9728|18176|14080|

# Quick and Dirty Estimates 

For the following scene:
- A single mesh with 50,000 vertices
- Screen resolution of 1920x1080

We need the shader units to process 50,000 vertices and 2,073,600 pixels

On a video card with 2048 shader units, we can expect each shader unit to run either some vertex shader or fragment shader code 1,036 times each frame

# Shader Programs

Shader programs get run on the shader units when you call glDrawArrays.

If you call a draw function with a vertex buffer object filled with 50,000 vertices, the following will happen:
- the vertex shader program will run 50,000 times
- it will run as many programs simultaneously as the video card allows
- the code for each program run is exactly the same
- only the inputs to each program will change
	- i.e. Each of the instances of the program receive the attributes of a different vertex
	- The uniform values are the same for all 50,000 instances

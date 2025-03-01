
# Overview

Visual Studio solution and project files can be created and maintained by hand, but this isn't sustainable in big projects, especially ones that support multiple platforms.

Many tools are available that help with this issue, including:
- CMake - https://cmake.org/
- Premake - https://premake.github.io/
- Genie - https://github.com/bkaradzic/GENie
- Sharpmake - https://github.com/ubisoft/Sharpmake
- etc

These tools are capable of generating project files for Visual Studio, XCode, GNU Makefiles and others.

CMake is likely the most prolific of the lot, but its also generally more complicated and can produce some messy output, but with some care can be quite good.

# CMake

## CMake Files

CMake works with text files containing descriptions of what the solution and project setup and options need to be. This file is generally called `cmakelists.txt`.

#### Full Example

```cmake
# Minimum Required Version of CMake
cmake_minimum_required( VERSION 3.10 )

# Solution
project( GameSolution )

# Project
add_executable( GameProject main.cpp )
```

Hopefully the example is self-explanatory. Some terminology is different than what Visual Studio uses, for example, in CMake a "project" refers to a "solution" in Visual Studio and an "executable" refers to an exe "project" (as opposed to a library)

## Running CMake to Generate the Solution/Project Files

#### Bad Approach

From command line, inside the folder with your cmakelists.txt file, you can run the following:

```Batchfile
cmake .
```

This will generate a ton of files in your current folder including a solution file. If you open the solution and build it, you'll see all the output files and folders also appear in this folder, making a mess of things.

#### Good Approach

Instead, to help contain all the files in a single folder that can be ignored by git, do the following

```Batchfile
mkdir build
cd build
cmake ..
```

## Options

#### Adding Multiple Files

```cmake
file( GLOB_RECURSE GameSourceFiles
	Source/*.cpp
	Source/*.h
)

add_executable( GameProject ${GameSourceFiles} )
```

The ${} syntax is used to reference variables as opposed to file or folder names

#### Include Directories

```cmake
target_include_directories( GameProject PUBLIC
	Source
)
```

#### Compiler Settings

```cmake
target_compile_features( GameProject PRIVATE cxx_std_17 )
```

#### Creating Library Projects

```cmake
add_library( Framework ${FrameworkSourceFiles} )
```

#### Linking Libraries

```cmake
target_link_libraries( GameProject
	Framework
	opengl32
)
```

## Splitting Projects into their own Folders

CMake is designed to have one cmakelists file include other project, with each project defining their own project in their own cmakelists file

For example, we might setup our directory structure like this:

- Root
	- cmakelists.txt
	- Game
		- cmakelists.txt
		- Source
			- source files...
	- Framework
		- cmakelists.txt
		- Source
			- source files...

The cmakelists.txt file in the root folder could then look like this:

```cmake
cmake_minimum_required( VERSION 3.10 )

project( GameSolution )

add_subdirectory( Framework )
add_subdirectory( Game )
```

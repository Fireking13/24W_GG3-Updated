
# Prerequisite Knowledge

[Command Prompt](Command%20Prompt.md)

# Environment Variables

Windows allows you to create variables. These can be defined system-wide, per user, or per running instance of an application.

You can see what variables have been defined with the `set` command. For example, some of my system's variables look like this:

```
ALLUSERSPROFILE=C:\ProgramData
APPDATA=C:\Users\me\AppData\Roaming
NUMBER_OF_PROCESSORS=8
Path=C:\WINDOWS\system32;C:\WINDOWS;C:\Program Files\Git\cmd;C:\Program Files\CMake\bin
windir=C:\WINDOWS
```

These can be accessed by applications (like visual studio), batch files and from the command line itself.

#### Example Usage

if you have a large library like Boost, OpenCV, or others, you don't want to install a copy for every project you're working on. Instead you install each to a single shared directory for use by multiple projects. Then set its location in an environment variable, like this:

```
set OPENCV_DIR=c:\OpenCV\
```

This will only set the value for the instance of the command prompt you're running. To set the value system-wide, do the following instead

```
setx /M OPENCV_DIR c:\OpenCV\
```

This allows projects to access the library without hard-coding a location, which allows different users on different machines the option to put the library into any folder or on any drive.

# Path

"Path" is an important environment variable that the system uses to run programs

If your Path is set as follows:

```
Path=C:\WINDOWS\system32;C:\WINDOWS;C:\Program Files\Git\cmd;C:\Program Files\CMake\bin
```

Then, if you run a tool like cmake.exe from command line, it will check each of the following in order to find the executable file:

- The current directory
- Then each folder listed in the Path variable, one by one

Tools often give the option to add their "binary" folder to the Path during installation

#### Extending the Path

You can add on to the Path by redefining it using the old value 

```
set Path=%Path%;c:\OpenCV
```

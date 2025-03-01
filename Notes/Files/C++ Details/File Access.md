
# Current Working Directory

**When an executable is run**, by default it will look for files starting in **it's own folder**.
You can still open files from:
- any relative folder (*"Data/file.txt"*, *"../Data/file.txt"*)
- or absolute folder (*"C:/Data/file.txt"*)

When **launching with the debugger** in Visual Studio, the current working directory defaults to **the project folder**. This can be changed in Project Settings -> Debugging

# Code for Reading a File

**fopen approach in C/C++**

```c++
// Headers: <stdio.h>

FILE* pFile = fopen( "myfile.txt", "rb" );
if( pFile )
{
	char buffer[256];
	fread( buffer, 1, 256, pFile );
	fclose();
}
```

**fstream approach in C++**

```c++
// Headers: <iostream> and <fstream>

ifstream file( "myfile.txt", ios::in|ios::binary );
if( file.is_open() )
{
	char buffer[256];
	file.read( buffer, 256 );
    myfile.close();
}
```


# What Do These Words Mean?

**Declarations** are statements that say the things exists
**Definitions** are the actual thing

You can *declare* something **as many times as you like**, but you can only *define* it **once**.

You can't use a variable of function that hasn't been declared yet, so declarations are often placed at the top of files or inside heads that are included at the top of files.

Definitions are rarely put in headers, since they will be defined twice if 2 or more files include that header.

# Examples

#### Function Declaration
```c++
int DoStuff(int a, int b);
```

#### Function Definition
```c++
int DoStuff(int a, int b)
{
	return a+b;
}
```

#### Local Variable Declaration/Definition
```c++
int main()
{
	int a;
}
```

#### Global Variable Declaration
```c++
extern int g_Value;
```

#### Global Variable Declaration/Definition
```c++
int g_Value;
```

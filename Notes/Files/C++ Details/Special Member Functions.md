
# Implicit Methods

There are a 6 methods that the compiler will generate for you if you don't manually create them. These are *implicit functions*, which will be created by the compile if called, as opposed to normal methods which are explicitly written by the programmer.

These are also known as *default* methods. i.e. Default constructor, Default destructor, etc.

# Common Ones

- Default Constructor
	- If you don't add any constructor to your class, a default constructor will be created for you
	- If you explicitly create any constructor this won't be generated
	- It will call:
		- The parent class default constructor, if needed
		- The default constructor of any members variable instances
			- This is always automatic when the instances get created
- Destructor
	- An empty method, does nothing and isn't virtual

# Copy and Move

The *copy constructor* and *copy assignment operator* (equal operator) are also generated automatically. These default versions will simply do shallow copies of the objects, which may or may not be desired.

The *move constructor* and *move assignment operator* as well, but we haven't discussed these yet.

# Explicitly Creating These Methods

These methods can be replaced by explicit versions in your class, or you can add single line stubs to explicitly say you're using the default or you chose not to use them at all, as follows:

```c++
// Don't create default methods.
MyClass(const MyClass& other) = delete;
MyClass& operator=(const MyClass& other) = delete;
MyClass(MyClass&& other) = delete;
MyClass& operator=(MyClass&& other) = delete;
```

or

```c++
// Create the default versions.
MyClass() = default;
~MyClass() = default;
MyClass(const MyClass& other) = default;
MyClass& operator=(const MyClass& other) = default;
MyClass(MyClass&& other) = default;
MyClass& operator=(MyClass&& other) = default;
```

# Extra Rules

There are a series of rules for when these special functions get generated or something prevents them from being generated, you can look those up on the link provided below, if interested.

# Full List

From Wikipedia:

Here are the signatures of the special member functions:

|Function|syntax for class MyClass|
|---|---|
|Default constructor|`MyClass();`|
|Copy constructor|`MyClass(const MyClass& other);`|
|Move constructor|`MyClass(MyClass&& other) noexcept;`|
|Copy assignment operator|`MyClass& operator=(const MyClass& other);`|
|Move assignment operator|`MyClass& operator=(MyClass&& other) noexcept;`|
|Destructor|`~MyClass();`|
|The 'address of' operator|`MyClass *operator&(void);`  <br>`MyClass const *operator&(void) const;`  <br>`MyClass volatile *operator&(void) volatile;`  <br>`MyClass const volatile *operator&(void) const volatile;`|

**Note:** I changed the table from Wikipedia, which had the default destructor marked as virtual, it won't be.

# More Info

https://cplusplus.com/doc/tutorial/classes2/
https://en.wikipedia.org/wiki/Special_member_functions

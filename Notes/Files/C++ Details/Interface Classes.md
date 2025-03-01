aka Abstract Classes
aka Protocols

# What are Interface classes?

Interface classes are classes that purely define how the user will interact with them. i.e. They provide an interface through which they can be used, but shouldn't provide any functionality.

This allows us to define a common set of methods that can be used to talk to any subclass of a class without knowing anything about each subclass.

Some languages, like Java and C#, support interfaces natively, these classes **cannot** define any methods or member variables. When using the `interface` keyword in there languages, the compiler will produce errors when methods have definitions or variables are added to the interface's definition.

**C++ doesn't have support for interfaces** built into the language, so we **imitate the concept of interfaces with abstract classes**, but nothing prevents definitions and member variables from being added to the class.

# What are Abstract Classes?

Abstract classes are classes that contain one or more pure virtual methods.

Pure Virtual Methods are methods that have no definition, declared as follows:
```c++
virtual void Update() = 0;
```

Since some methods don't have definitions/bodies, you can't create an instance of the class. The compiler will give an error if you try.

# Example

A common example of this is a shape class:
```
class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual float GetVolume() = 0;
	virtual void Draw() = 0;
}
```

This tells us any subclass of the Shape class will need to support at least 2 methods (`GetVolume()` and `Draw()`) since the shape class defined these 2 methods as **pure virtual**. The = 0 indicates that these are pure virtual methods and have no bodies/definitions associated with them.

This means any class that inherits this Shape class must provide an implementation for these 2 functions, or it will also be abstract and can't be instantiated.

This also guarantees that any instantiable subclass of Shape will support these 2 methods and any code that does create a Square or a Circle, for example, is guaranteed to be able to call these 2 methods.

A Square class would be said to "implement the Shape interface".

# Use Case

#### Communicating Between Libraries
We're going to use an Interface class to communicate between the Framework library and the Game project code.

In this case, we want the Framework project to control the main flow of the game, but the Framework doesn't know anything about the Game project.

By defining an interface in the Framework project, the Game project can implement that interface. i.e. create a subclass and give all the pure virtual methods an override.

# GameCore class

To do this, we'll create:

In the Framework project:
- An abstract class called GameCore. i.e. the interface
	- We want a methods in there for Update and Draw to start with

In the Game project:
- A class called Game that inherits from GameCore
	- This will override the Update and Draw and do 

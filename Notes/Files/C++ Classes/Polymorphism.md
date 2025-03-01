
# Definition

Polymorphism is the ability for one object to take the form of another.
In C++ terms, it involves assigning a subclass to a pointer of a parent type.

# Example

First we define a base class:
```
class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual float GetVolume();
	virtual void Draw();
};
```

We can then define subclasses of Shape:
```c++
class Circle : public Shape
{
public:
	Circle();
	virtual ~Circle();
	virtual float GetVolume() override;
	virtual void Draw() override;
};
```

Then we can create instances of these classes and store their address in a base class pointer:
```c++
Shape* pShape = new Circle();
```
or
```c++
Shape* pShape = new Box();
```


This is especially useful when you have many objects that are subclasses of the base class type.
```c++
std::vector<Shape*> shapes;
shapes.push_back( new Circle() );
shapes.push_back( new Box() );

for( Shape* pShape : shapes )
{
	pShape->Draw();
}
```

In this case, the `pShape->Draw();` command will either call `Circle::Draw()` or `Box::Draw()` depending on what subclass of Shape the pShape pointer is pointing to.
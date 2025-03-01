
**NOTE**: memory sizes aren't always this easy to determine, memory alignment issues could complicate it, so don't treat the numbers in these examples as facts. See [Struct Padding](Struct%20Padding) if I ever write it.

#### Simple Class

When you create an instance of a class, the compiler needs to know how much memory it will take.

For example:
```c++
class GameObject
{
public:
	int m_ID;
	float m_PosX;
	float m_PosY;
};
```

This class is 12 bytes large:
- 4 bytes for an int
- 4 bytes per float with 2 floats.

#### Nested Class

If instead we had a vec2 class, and we declared GameObject like this:
```c++
class vec2
{
	float x, y;
};

class GameObject
{
public:
	int m_ID;
	vec2 m_Pos;
};
```

GameObject would still be 12 bytes large, because a vec2 is 8 bytes + 4 for the int.

For the compiler to determine this, the vec2 class needs to be fully defined before the GameObject uses it, so it it was in a different header, that header would need to have been included before we defined the GameObject class.

#### Nested Class with Forward Declaration

We generally want to avoid includes inside header, they often lead to circular include patterns. So when possible we **forward declare** classes inside headers.

```c++
class vec2
{
	float x, y;
};

class GameObject
{
public:
	int m_ID;
	vec2 m_Pos;
	Mesh* m_pMesh;
};
```

Unlike the vec2 in this example, m_pMesh isn't a Mesh, it's a pointer to a Mesh. So the compiler doesn't need to know the size of the Mesh class, just the size of a pointer.

In 64-bit mode, a pointer is 64 bits (or 8 bytes) big. So, our GameObject is 20 bytes large (See **NOTE** at the top, it's actually 24 bytes)

Since we don't need to know the size of Mesh, we don't need to include Mesh.h, we only need let the compiler know the word "Mesh" isn't a typo. To do that we *forward declare* it. This let's the compiler know "Mesh" is a class name, without having to include Mesh.h.

```c++
class Mesh; // Forward declaration.

class vec2
{
	float x, y;
};

class GameObject
{
public:
	int m_ID;
	vec2 m_Pos;
	Mesh* m_pMesh;
};
```

Now, if we need to use the Mesh class by accessing it's methods or member vars, the compiler needs to know everything about it, so an include is required.

```c++
void GameObject::Draw()
{
	m_pMesh->Draw(); // This won't work without an including Mesh.h up above.
}
```

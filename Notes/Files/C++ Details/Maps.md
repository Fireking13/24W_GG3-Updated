
Maps, often known as dictionaries in other languages, are a templated class that let you associate any value with any type of index/key.

You can think of them like arrays where you're not limited to numbers as the index.

They're defined like this:

```c++
	std::map<key type, value type>
```

or more concretely

```c++
	std::map<int, std::string>
```

#### Example

Take a phone book as an example. In this case, we associate a name to a phone number, like this:

|Name|Phone Number|
|:----------:|:-------------:|
|Alex|555-1234|
|Bob|555-9876|
|Chris|555-5555|

The name can be stored as a string and so can the phone number.

So, we would define our map as the following data type:

```c++
	//          name         phone#
	std::map<std::string, std::string>
```

#### Another example

We can use a map as a list of resources for our game. Each Mesh we create can be stored in an entry that we can look up by name.

|Mesh name|Mesh pointer|
|:----------:|:-------------|
|Circle|new Mesh(circleVerts)|
|Box|new Mesh(boxVerts)|
|Tree|new Mesh(treeVerts)|

The name can be stored as a string, the mesh pointer is simply a mesh pointer.

So, we would define our map as the following data type:

```c++
	std::map<std::string, fw::Mesh*>
```

So, instead of this:

```c++
	// This needs new member vars for each mesh instance we want to create.
	m_CircleMesh = new Mesh(circleVerts);
	m_BoxMesh = new Mesh(boxVerts);
	m_TreeMesh = new Mesh(treeVerts);
```

We would have this:

```c++
	// This allows us to create as many meshes as we want without changing the class
	m_Meshes["Circle"] = new Mesh(circleVerts);
	m_Meshes["Box"] = new Mesh(boxVerts);
	m_Meshes["Tree"] = new Mesh(treeVerts);
```

# Adding and Removing Entries:

Let's say we want to associate students with their grades

First declare a map:

```c++
	std::map<std::string, float> m_StudentGrades;
```

Adding entries:

```c++
	m_StudentGrades["Joe"] = 83;
	m_StudentGrades["Jane"] = 88;
```

Removing entries:

```c++
	m_StudentGrades.erase( "Joe" );
```

Looking up values:

```c++
	// Watch out for this:
	int grade = m_StudentGrades["Fred"];
	// If Fred isn't in the map,
	//     this will insert a default value in that key and return it.
	// This is fine if you know the key is already in the map.

	// Proper way if you're unsure the key exists:
	auto it = m_StudentGrades.find("Fred");
	if( it != m_StudentGrades.end() )
	{
		int grade = it->second;
	}
```

# Details

- Each key is unique
	- You can't have two different values help in the same index
	- unless: `std::map<std::string, std::vector<std::string>`
- Keys are stored in sorted order
	- If you iterate over the list, you'll visit each key once in order
	- If you don't care about order `unordered_map` is a bit faster
- Looking up items by their key is fast
	- but iterating over the whole list is slower than using a vector
- Maps will grow/shrink as you add/remove items

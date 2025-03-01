
This resource manager implementation involves the following topics:
- inheritance/polymorphism
- [Maps](../C++%20Fine%20Details/Maps.md)
- pairs
- templating

It's designed to allow any type of resource to live inside 2 maps:
- One for the categories of resources
- One for the list of individual resources within a category

This manager will also destroy all resources when it's destroyed.

```c++
#pragma once

#include "CoreHeaders.h"

// ResourceManager Usage:
//     Create a resource and adding it to the manager:
//         resourceManager.Add<Texture>( "Mailbox", new Texture(...) );
//     Ask the manager for an existing resource:
//         Texture* pTexture = resourceManager.Get<Texture>( "Mailbox" );

// New resources need to inherit from Resource and define a static categoryID method.
// For example:
//     static ResourceCategoryIDType GetResourceCategoryID() { return "Mesh"; }

namespace fw {

class Resource
{
public:
	virtual ~Resource() {}
};

using ResourceCategoryIDType = const char*;
using ResourceIDType = std::string;

class ResourceManager
{
public:
	~ResourceManager()
	{
        for( auto& resourceCategoryPair : m_Resources )
        {
            for( auto& resource : resourceCategoryPair.second )
            {
                delete resource.second;
            }
        }
	}
	
	template <class Type> void Add(ResourceIDType name, Type* pResource)
	{
		m_Resources[Type::GetResourceCategoryID()][name] = pResource;
	}

	template <class Type> Type* Get(ResourceIDType name)
	{
		// If the category or the individual resource doesn't exist, assert.
		// This could return nullptr instead if you want to silently fail.
		if( m_Resources.count( Type::GetResourceCategoryID() ) == 0 ||
		    m_Resources[Type::GetResourceCategoryID()].count( name ) == 0 )
		{
			assert( false );
		}

		return static_cast<Type*>( m_Resources[Type::GetResourceCategoryID()][name] );
	}
	
protected:
	using ResourceList = std::map<ResourceIDType, Resource*>;
	std::map<ResourceCategoryIDType, ResourceList> m_Resources;
};

} // namespace fw
```

#### Example Resource subclass:

```c++
class Mesh : public Resource
{
public:
	// Mesh constructor and any other mesh methods.

	static ResourceCategoryIDType GetResourceCategoryID() { return "Mesh"; }
	
protected:
	// All the usual Mesh member variables.
}
```

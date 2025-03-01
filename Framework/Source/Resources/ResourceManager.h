#pragma once

#include "CoreHeaders.h"

namespace fw {

	// New Resource type needs to inherit from Resource and define a static category ID method.
	//     For example: static ResourceCategoryIDType GetResourceCategoryID() { return "Mesh"; }

	class Resource
	{
	public:
		virtual ~Resource() {}
	};

	// ResourceManager Usage:
	//     Create a resource and adding it to the manager:
	//         resourceManager.Add<Texture>( "Mailbox", new Texture(...) );
	//     Ask the manager for an existing resource:
	//         Texture* pTexture = resourceManager.Get<Texture>( "Mailbox" );

	using ResourceCategoryIDType = const char*;
	using ResourceIDType = std::string;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		void Editor_DisplayResourceLists();

		template <class Type> void Add(ResourceIDType name, Type* pResource)
		{
			m_Resources[Type::GetResourceCategoryID()][name] = pResource;
		}

		template <class Type> Type* Get(ResourceIDType name)
		{
			// If the category doesn't exist or the individual resource doesn't exist, assert.
			// This could return nullptr instead if you want to silently fail.
			if( m_Resources.count( Type::GetResourceCategoryID() ) == 0 ||
				m_Resources[Type::GetResourceCategoryID()].count( name ) == 0 )
			{
				assert( false );
			}

			return static_cast<Type*>( m_Resources[Type::GetResourceCategoryID()][name]);
		}

	protected:
		using ResourceList = std::map<ResourceIDType, Resource*>;
		std::map<ResourceCategoryIDType, ResourceList> m_Resources;
	};

} // namespace fw

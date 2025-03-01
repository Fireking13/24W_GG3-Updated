#pragma once
#include "Objects/GameObject.h"

namespace JPH {
    class PhysicsSystem;
    class TempAllocatorImpl;
    class JobSystemThreadPool;
    class Body;
}

namespace fw {

    class BPLayerInterfaceImpl;
    class ObjectVsBroadPhaseLayerFilterImpl;
    class ObjectLayerPairFilterImpl;

    class JoltWorldBundle
    {
    public:
        JPH::PhysicsSystem* m_pWorld = nullptr;
        JPH::JobSystemThreadPool* m_pJobSystem = nullptr;
        JPH::TempAllocatorImpl* m_pTempAllocator = nullptr;

        BPLayerInterfaceImpl* m_pBroadPhaseLayerInterface = nullptr;
        ObjectVsBroadPhaseLayerFilterImpl* m_pObjecVsBroadphaseLayerFilter = nullptr;
        ObjectLayerPairFilterImpl* m_pObjectVsObjectLayerFilter = nullptr;
    };

    JoltWorldBundle* CreateJoltWorld();
    void UpdateJoltWorld(JoltWorldBundle* pBundle, float deltaTime);
    void DestroyJoltWorld(JoltWorldBundle* pBundle);

    JPH::Body* CreateJoltBody(JPH::PhysicsSystem* pWorld, vec3 pos, vec3 rot, vec3 scale, bool isDynamic, float density, GameObject* pGameObject);
    void DestroyJoltBody(JPH::PhysicsSystem* pWorld, JPH::Body* pBody);

} // namespace fw
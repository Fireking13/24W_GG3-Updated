//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "Jolt/JoltHelpers.h"


class Camera;
class VirtualController;
class Player;

namespace fw {

    class Scene
    {
    public:
        Scene(GameCore* gameCore);
        virtual ~Scene();

        virtual void Update(float deltaTime) = 0;
        virtual void Draw() = 0;
        virtual void OnEvent(fw::Event* pEvent) = 0;
        //virtual void OnEvent(Event* pEvent) = 0;

        //getters
        VirtualController* getVirtualController() { return m_pVirtualController; }
        std::vector<GameObject*> getObjects() { return m_Objects; }
        Camera* getCamera() { return m_pCamera; }
        std::string GetName() { return m_Name; }

    protected:

        std::string m_Name;

        Camera* m_pCamera = nullptr;
        Player* m_pPlayer = nullptr;
        b2World* m_pWorld = nullptr;

        JoltWorldBundle* m_pJoltWorld = nullptr;

        std::vector<GameObject*> m_Objects;

        VirtualController* m_pVirtualController = nullptr;

        GameCore* m_pGameCore = nullptr;
    };

} // namespace fw

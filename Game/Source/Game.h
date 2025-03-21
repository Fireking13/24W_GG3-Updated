//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "ScenesSystem/Scene.h"

class Player;
class VirtualController;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void CreateUniforms();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    fw::ResourceManager* GetResources() { return m_pResources; }

    void Editor_DisplayCustomPopUp(std::string name, std::string& data);
protected:
    // Editor Interface.
    fw::ImGuiManager* m_pImGuiManager = nullptr;
    void Editor_DisplayObjectList();
    void Editor_DisplayResources();
    void Editor_DisplayScene();
    

    // Resources.
    fw::ResourceManager* m_pResources = nullptr;

    fw::EventManagement* m_pEventManager = nullptr;

    std::vector<fw::Scene*> m_Scenes;
    fw::Scene* m_ActiveScene = nullptr;
};

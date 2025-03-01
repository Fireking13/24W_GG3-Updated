#include "DemoScene.h"
//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "Objects\VirtualController.h" 
#include "Objects/Camera.h"
#include "Game.h"

DemoScene::DemoScene(Game* pGame)
    : Scene(pGame)
{
    m_Name = "Demo";

	m_pCamera = new fw::Camera(m_pGameCore, vec3(5, 5, 0), vec3(0, 0, -25), vec3(0, 1, 0), vec3(0, 0, 3));

	m_pVirtualController = new VirtualController();

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    m_pPlayer = new Player(pGame, "Player", vec3(6, 5, 0), getMesh("Sprite"), getMaterial("MegaMan"));
    m_pPlayer->SetControler(m_pVirtualController);
    m_Objects.push_back(m_pPlayer);

    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Object 1", vec3(0, 0, 0), getMesh("Triangle"), getMaterial("VertexColor")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Object 2", vec3(10, 10, 0), getMesh("Triangle"), getMaterial("Blue")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Object 3", vec3(5, 5, 0), getMesh("Square"), getMaterial("VertexColor")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Object 4", vec3(1, 1, 0), getMesh("Square"), getMaterial("VertexColor")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Object 5", vec3(1, 9, 0), getMesh("Square"), getMaterial("Blue")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Object 6", vec3(0, 5, 0), getMesh("Circle"), getMaterial("Blue")));
}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{


    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    m_pCamera->Update(deltaTime);
}

void DemoScene::Draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);

    // Draw all objects.
    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Draw(m_pCamera);
    }
}

void DemoScene::OnEvent(fw::Event* pEvent)
{
}

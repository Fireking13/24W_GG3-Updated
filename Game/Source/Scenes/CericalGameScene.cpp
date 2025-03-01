#include "CericalGameScene.h"
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


CericalScene::CericalScene(Game* pGame)
    : Scene(pGame)
{

    m_Name = "Cerical Game";

    m_pCamera = new fw::Camera(m_pGameCore, vec3(0, 0, 0), vec3(0, -50, -25), vec3(0, 1, 0), vec3(0, 0, 0)); //-15

	m_pVirtualController = new VirtualController();

    m_pWorld = new b2World(b2Vec2(0, -10));

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    uint16 BoxGroup = PhysicsCategoriesCerical;

    /*fw::GameObject* pCerical = new fw::GameObject(m_pGameCore, "WaterPlane", vec3(0, 0, 0), getMesh("WaterPlane"), getMaterial("Water")); //Water
    m_Objects.push_back(pCerical);*/

    fw::GameObject* pCerica = new fw::GameObject(m_pGameCore, "Land", vec3(0, 0, 0), getMesh("Land"), getMaterial("WaterNoWave"));
    m_Objects.push_back(pCerica);

    pObject3 = new fw::GameObject(m_pGameCore, "Object 3", vec3(5, 0, 0), getMesh("Tree"), getMaterial("Dice"));
    pObject3->SetScale(vec3(0.1f, 0.1f, 0.1f));
    pObject3->SetRotation(vec3(90, 0, 0));
    m_Objects.push_back(pObject3);


    //m_pWorld->SetContactListener(m_ContactListener);
}

CericalScene::~CericalScene()
{
    //delete m_ContactListener;
}

void CericalScene::Update(float deltaTime)
{
    m_pWorld->Step(1 / 60.0f, 8, 3);

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    pObject3->SetRotation(vec3(pObject3->GetRotation().x + 1, 0, 0));

    if (m_pVirtualController != nullptr)
    {
        if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Jump)) //when held the padles go up
        {

        }
    }

    m_pCamera->Update(deltaTime);
}

void CericalScene::Draw()
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

void CericalScene::OnEvent(fw::Event* pEvent)
{
}

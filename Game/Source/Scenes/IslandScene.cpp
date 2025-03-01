#include "IslandScene.h"
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
#include <random>
#include "Game.h"


IslandScene::IslandScene(Game* pGame)
    : Scene(pGame)
{

    m_Name = "Island Game";

    m_pCamera = new fw::Camera(m_pGameCore, vec3(5, 5, 0), vec3(0, 10, -5), vec3(0, 1, 0), vec3(0, 0, 0)); //-15

	m_pVirtualController = new VirtualController();

    m_pWorld = new b2World(b2Vec2(0, -10));

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    fw::GameObject* pWater = new fw::GameObject(m_pGameCore, "WaterPlane", vec3(-5, 0.2, -5), getMesh("WaterPlane"), getMaterial("Water")); //Water
    m_Objects.push_back(pWater);

    fw::GameObject* pLand = new fw::GameObject(m_pGameCore, "Land", vec3(0, 0, 0), getMesh("Land"), getMaterial("HightMap"));
    m_Objects.push_back(pLand);

    std::random_device randD;
    std::mt19937 gen(randD()); 
    std::uniform_int_distribution<> RandomX(0, pLand->GetMesh()->getXValue());
    std::uniform_int_distribution<> RandomY(0, pLand->GetMesh()->getZValue());
    std::uniform_int_distribution<> RandomAngle(-360, 360);
    std::uniform_int_distribution<> RandomSize(-20, 20);

    for (int i = 0; i < 10; i++)
    {
        float size = ((RandomSize(gen) / 100.0f) + 1);

        fw::GameObject* pTree = new fw::GameObject(m_pGameCore, "Tree", pLand->GetMesh()->getPos(RandomX(gen), RandomY(gen)), getMesh("TreeStanding"), getMaterial("TreeColourMat"));
        pTree->SetScale(vec3(size, size, size));
        pTree->SetRotation(vec3(0, RandomAngle(gen), 0));

        m_Objects.push_back(pTree);
    }
    

    fw::GameObject* pCube1 = new fw::GameObject(m_pGameCore, "Cube 1", vec3(0, 0, 0), getMesh("Cube"), getMaterial("White"));
    m_Objects.push_back(pCube1);

    fw::GameObject* pCube2 = new fw::GameObject(m_pGameCore, "Cube 2", vec3(10, 0, 0), getMesh("Cube"), getMaterial("White"));
    m_Objects.push_back(pCube2);

    fw::GameObject* pCube3 = new fw::GameObject(m_pGameCore, "Cube 3", vec3(0, 0, 10), getMesh("Cube"), getMaterial("White"));
    m_Objects.push_back(pCube3);

    fw::GameObject* pCube4 = new fw::GameObject(m_pGameCore, "Cube 4", vec3(10, 0, 10), getMesh("Cube"), getMaterial("White"));
    m_Objects.push_back(pCube4);
}

IslandScene::~IslandScene()
{
    //delete m_ContactListener;
}

void IslandScene::Update(float deltaTime)
{
    m_pWorld->Step(1 / 60.0f, 8, 3);

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    

    if (m_pVirtualController != nullptr)
    {
        if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Jump)) //when held the padles go up
        {

        }
    }

    m_pCamera->Update(deltaTime);
}

void IslandScene::Draw()
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

void IslandScene::OnEvent(fw::Event* pEvent)
{
}

#include "CubeScene.h"
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

CubeScene::CubeScene(Game* pGame)
    : Scene(pGame)
{
    m_Name = "Cube";

    m_SpinSpeed = 1.0f;

	m_pCamera = new fw::Camera(m_pGameCore, vec3(5, 5, 0), vec3(0, 0, -25), vec3(0, 1, 0), vec3(0, 0, 3));

	m_pVirtualController = new VirtualController();

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Dice 1", vec3(0, 0, 0), getMesh("Dice"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Dice 2", vec3(5, 5, 0), getMesh("Dice"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Dice 3", vec3(10, 10, 10), getMesh("Dice"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Dice 4", vec3(1, 6, 4), getMesh("Dice"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "Dice 5", vec3(1, 2, 8), getMesh("Dice"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(m_pGameCore, "box", vec3(2, 2, 10), getMesh("Cube"), getMaterial("Blue")));

}

CubeScene::~CubeScene()
{

}

void CubeScene::Update(float deltaTime)
{
    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
        pObject->SetRotation(vec3(0, pObject->GetRotation().y + m_SpinSpeed, 45)); //spins to the right and is slanted at 45 dgrees
    }

    m_pCamera->Update(deltaTime);
}

void CubeScene::Draw()
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

void CubeScene::OnEvent(fw::Event* pEvent)
{
}

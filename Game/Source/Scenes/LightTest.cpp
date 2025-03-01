#include "LightTest.h"
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
#include "Objects/ThridPersonCamera.h"
#include "Game.h"
#include "Utility/Uniforms.h"
#include <string>

LightTest::LightTest(Game* pGame)
    : Scene(pGame)
{

    m_Name = "Lighting Test Game";

    m_pWorld = new b2World(b2Vec2(0, -10));

    m_pVirtualController = new VirtualController();

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    pLand = new fw::GameObject(m_pGameCore, "Land", vec3(0, 0, 0), getMesh("Land"), getMaterial("GrassWithLight"));
    m_Objects.push_back(pLand);

    m_pPlayer = new Player(pGame, "Player", pLand->GetMesh()->getPos(16, 16), getMesh("PlayerPot"), getMaterial("WaterTexWithLight"));
    m_pPlayer->SetControler(m_pVirtualController);
    m_Objects.push_back(m_pPlayer);

    std::random_device randD;
    std::mt19937 gen(randD());
    std::uniform_int_distribution<> RandomX(0, pLand->GetMesh()->getXValue());
    std::uniform_int_distribution<> RandomY(0, pLand->GetMesh()->getZValue());
    std::uniform_int_distribution<> RandomAngle(-360, 360);
    std::uniform_int_distribution<> RandomSize(-20, 20);

    for (int i = 0; i < 10; i++)
    { 
        float size = ((RandomSize(gen) / 100.0f) + 1);

        fw::GameObject* pTree = new fw::GameObject(m_pGameCore, "Tree", pLand->GetMesh()->getPos(RandomX(gen), RandomY(gen)), getMesh("TreeStanding"), getMaterial("TreeWithLight"));
        pTree->SetScale(vec3(size, size, size));
        pTree->SetRotation(vec3(0, RandomAngle(gen), 0));

        m_Objects.push_back(pTree);
    }

    m_pCamera = new fw::ThridPersonCamera(m_pGameCore, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 0, 0), 10.0f, m_pPlayer);

    lightText = std::string(" ");
    m_Game = pGame;
}

LightTest::~LightTest()
{
}

void LightTest::Update(float deltaTime)
{
    m_pWorld->Step(1 / 60.0f, 8, 3);

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    vec3 playerRotation = m_pPlayer->GetRotation();
    playerRotation.y = m_pCamera->GetRotation().y + 180.0f;
    m_pPlayer->SetRotation(playerRotation);


    vec3 LightColour = vec3(1, 1, 1);
    float LightRange = 10.0f;

    vec3 lightPosOffSet = vec3(0, 1, 0);
    vec3 LightPos = m_pPlayer->GetPosition() + lightPosOffSet;

    float LightFalloff = 1.0f;
    float LightAmbientPer = 0.2f;

    fw::Uniforms* pUniforms = m_pGameCore->GetUniforms();
    bgfx::setUniform(pUniforms->GetUniform("u_LightColour"), &LightColour);
    bgfx::setUniform(pUniforms->GetUniform("u_LightRange"), &LightRange);
    bgfx::setUniform(pUniforms->GetUniform("u_LightPos"), &LightPos);

    bgfx::setUniform(pUniforms->GetUniform("u_LightFalloff"), &LightFalloff);
    bgfx::setUniform(pUniforms->GetUniform("u_LightAmbientPer"), &LightAmbientPer);

    if (m_pVirtualController != nullptr)
    {
        float movementSpeed = 2.0f;

        if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Up))
        {
            m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_pPlayer->GetForwardVector() * movementSpeed * deltaTime);
        }
        else if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Down))
        {
            m_pPlayer->SetPosition(m_pPlayer->GetPosition() - m_pPlayer->GetForwardVector() * movementSpeed * deltaTime);
        }

        if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Left))
        {
            m_pPlayer->SetPosition(m_pPlayer->GetPosition() - m_pPlayer->GetRightVector() * movementSpeed * deltaTime);
        }
        else if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Right))
        {
            m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_pPlayer->GetRightVector() * movementSpeed * deltaTime);
        }
    }

    float hight = pLand->GetMesh()->GetHeightAtXZ(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().z);
    m_pPlayer->SetPosition(vec3(m_pPlayer->GetPosition().x, hight, m_pPlayer->GetPosition().z));


    lightText.clear();
    lightText.append("Light Pos: ").append(std::to_string(LightPos.x)).append(", ").append(std::to_string(LightPos.y)).append(", ").append(std::to_string(LightPos.z));
    lightText.append("\nLight Range: ").append(std::to_string(LightRange));
    lightText.append("\nLight Colour: ").append(std::to_string(LightColour.x));
    lightText.append("\nLight Falloff: ").append(std::to_string(LightFalloff));
    lightText.append("\nLight Ambient%: ").append(std::to_string(LightAmbientPer));

    m_Game->Editor_DisplayCustomPopUp(std::string("Light Info"), lightText);

    m_pCamera->Update(deltaTime);
}

void LightTest::Draw()
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

void LightTest::OnEvent(fw::Event* pEvent)
{
}

#include "Final.h"
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

#include "Jolt/Jolt.h"
#include "JoltPhysics/Jolt/RegisterTypes.h"
#include "JoltPhysics/Jolt/Core/Factory.h"
#include "JoltPhysics/Jolt/Core/JobSystemThreadPool.h"
#include "JoltPhysics/Jolt/Core/TempAllocator.h"
#include "JoltPhysics/Jolt/Physics/Body/BodyActivationListener.h"
#include "JoltPhysics/Jolt/Physics/Body/BodyCreationSettings.h"
#include "JoltPhysics/Jolt/Physics/Collision/Shape/BoxShape.h"
#include "JoltPhysics/Jolt/Physics/Collision/Shape/SphereShape.h"
#include "JoltPhysics/Jolt/Physics/PhysicsSettings.h"
#include "JoltPhysics/Jolt/Physics/PhysicsSystem.h"

FinalScene::FinalScene(Game* pGame)
    : Scene(pGame)
{
    m_Name = "Final Scene";

    m_pJoltWorld = fw::CreateJoltWorld();

    m_pVirtualController = new VirtualController();

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    pLand = new fw::GameObject(m_pGameCore, "Land", vec3(0, 0, 0), getMesh("LandFlat"), getMaterial("GrassWithLight"));
    m_Objects.push_back(pLand);

    playerStart = vec2(26, 5);
    holeMiddle = vec2(12, 20);

    m_pPlayer = new Player(pGame, "Player", pLand->GetMesh()->getPos((int)playerStart.x, (int)playerStart.y), getMesh("Ball"), getMaterial("WaterTexWithLight"));
    m_pPlayer->SetControler(m_pVirtualController);
    m_Objects.push_back(m_pPlayer);

    pHole = new fw::GameObject(m_pGameCore, "Hole", pLand->GetMesh()->getPos((int)holeMiddle.x, (int)holeMiddle.y), getMesh("Hole"), getMaterial("WaterTexWithLight"));
    m_Objects.push_back(pHole);


    std::random_device randD;
    std::mt19937 gen(randD());
    std::uniform_int_distribution<> RandomX(0, (int)pLand->GetMesh()->getXValue());
    std::uniform_int_distribution<> RandomY(0, (int)pLand->GetMesh()->getZValue());
    std::uniform_int_distribution<> RandomAngle(-360, 360);

    for (int i = 0; i < 10; i++)
    { 
        fw::GameObject* pTree = new fw::GameObject(m_pGameCore, "Tree", pLand->GetMesh()->getPos((int)RandomX(gen), (int)RandomY(gen)), getMesh("TreeStanding"), getMaterial("TreeWithLight"));
        pTree->SetRotation(vec3(0, (float)RandomAngle(gen), 0));

        m_Objects.push_back(pTree);
    }

    m_pCamera = new fw::ThridPersonCamera(m_pGameCore, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 0, 0), 5.0f, m_pPlayer);

    m_Game = pGame;

    power = 0; 
    maxPower = 9;
    powerDelayTimer = 0;
    powerDelayMax = 1.0f;

    inHole = false;
    lastHitPower = 0;
    strokes = 0;

    /*
    for (fw::GameObject* pObject : m_Objects)
    {
        vec3 pos = pObject->GetPosition();
        vec3 rot = pObject->GetRotation();
        vec3 scale = pObject->GetScale();

        float density = 1.0f;
        bool isDynamic = false;

        if (pObject->GetName() == "Player")
        {
            isDynamic = true;
            density = 1000.0f;
        }

        pObject->SetJoltBody(fw::CreateJoltBody(m_pJoltWorld->m_pWorld, pos, rot, scale, isDynamic, density, pObject));
    }*/
}

FinalScene::~FinalScene()
{
}

void FinalScene::Update(float deltaTime)
{
    fw::UpdateJoltWorld(m_pJoltWorld, deltaTime);

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


    if (!inHole) //and not moving
    {
       vec3 spot = pLand->GetMesh()->getPos((int)holeMiddle.x, (int)holeMiddle.y);

       vec3 playerPosition = m_pPlayer->GetPosition();

       float distance = (spot - playerPosition).Length();

       float threshold = 1.0f;

       if (distance < threshold)
       {
           inHole = true;
       }
    }

    if (m_pVirtualController != nullptr && !inHole)
    {
        if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Jump))
        {
            powerDelayTimer -= deltaTime;
            if (powerDelayTimer <= 0)
            {
                power++;

                if (power > maxPower)
                {
                    power = maxPower;
                }

                powerDelayTimer = powerDelayMax;
            }
        }

        if (m_pVirtualController->IsActionReleased(VirtualController::Actions::Jump))
        {
            vec3 forceDirection = m_pPlayer->GetForwardVector();

            float forceMagnitude = power * 10.0f;
            vec3 force = forceDirection * forceMagnitude;

            //m_pPlayer->GetJoltBody()->AddForce();

            lastHitPower = power;
            powerDelayTimer = 0;
            power = 0;
            strokes++;
        }

        if (m_pVirtualController->IsActionPressed(VirtualController::Actions::Reset))
        {
            reset();
        }
    }

    gameText.clear();
    if (inHole)
    {
        gameText.append("You Win :)");
        gameText.append("\nStrokes: ").append(std::to_string(lastHitPower));
    }
    else
    {
        gameText.append("Current Power: ").append(std::to_string(power));
        gameText.append("\nStrokes: ").append(std::to_string(strokes));
        gameText.append("\nLast Hit Power: ").append(std::to_string(lastHitPower));
    }

    m_Game->Editor_DisplayCustomPopUp(std::string("Golf Game Text"), gameText);

    m_pCamera->Update(deltaTime);
}

void FinalScene::Draw()
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

void FinalScene::OnEvent(fw::Event* pEvent)
{
}

void FinalScene::reset()
{
    m_pPlayer->SetPosition(pLand->GetMesh()->getPos((int)playerStart.x, (int)playerStart.y));

    for (fw::GameObject* pObject : m_Objects)
    {
        if (pObject->GetName() == "Tree")
        {
            std::random_device randD;
            std::mt19937 gen(randD());
            std::uniform_int_distribution<> RandomX(0, pLand->GetMesh()->getXValue());
            std::uniform_int_distribution<> RandomY(0, pLand->GetMesh()->getZValue());
            std::uniform_int_distribution<> RandomAngle(-360, 360);
            std::uniform_int_distribution<> RandomSize(-20, 20);

            pObject->SetPosition(pLand->GetMesh()->getPos((int)RandomX(gen), (int)RandomY(gen)));
            pObject->SetRotation(vec3(0.0f, (float)RandomAngle(gen), 0.0f));
        }
    }

    power = 0;
    powerDelayTimer = 0;
    inHole = false;
    lastHitPower = 0;
    strokes = 0;

    /*
    for (fw::GameObject* pObject : m_Objects)
    {
        vec3 pos = pObject->GetPosition();
        vec3 rot = pObject->GetRotation();
        vec3 scale = pObject->GetScale();

        float density = 1.0f;
        bool isDynamic = false;

        if (pObject->GetName() == "Player")
        {
            isDynamic = true;
            density = 1000.0f;
        }

        pObject->SetJoltBody(fw::CreateJoltBody(m_pJoltWorld->m_pWorld, pos, rot, scale, isDynamic, density, pObject));
    }*/
}

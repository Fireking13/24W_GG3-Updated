#include "Midterm.h"
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

bool leftwallHit = false;
bool rightwallHit = false;

MidtermScene::MidtermScene(Game* pGame)
    : Scene(pGame)
{

    m_Name = "Midterm (StressLand)";

    m_pCamera = new fw::Camera(m_pGameCore, vec3(0, 0, 0), vec3(0, 0, -25), vec3(0, 1, 0), vec3(0, 0, 0));

	m_pVirtualController = new VirtualController();

    m_pWorld = new b2World(b2Vec2(0, -10));

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>


    b2BodyDef bodyDef;
    b2Body* pGround = m_pWorld->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;

    uint16 LeftWallGroup = PhysicsCategoriesMidterm_Player;
    uint16 RightWallGroup = PhysicsCategoriesMidterm_Player;
    uint16 PlayerGroup = PhysicsCategoriesMidterm_Box | PhysicsCategoriesMidterm_WallRight | PhysicsCategoriesMidterm_WallLeft;
    uint16 BoxGroup = PhysicsCategoriesMidterm_Player;

    m_pPlayer = new Player(pGame, "Player", vec3(-8, 8, 0), getMesh("Sprite"), getMaterial("MegaMan"));
    m_pPlayer->SetControler(m_pVirtualController);
    m_pPlayer->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMidterm_Player, PlayerGroup, 0, false);
    m_Objects.push_back(m_pPlayer);

    pObject1 = new fw::GameObject(m_pGameCore, "Object 1", vec3(-4, 6, 0), getMesh("Square"), getMaterial("VertexColor"));
    pObject1->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMidterm_Box, BoxGroup, 0, false);
    m_Objects.push_back(pObject1);

    pObject2 = new fw::GameObject(m_pGameCore, "Object 2", vec3(4, 6, 0), getMesh("Square"), getMaterial("VertexColor"));
    pObject2->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMidterm_Box, BoxGroup, 0, false);
    m_Objects.push_back(pObject2);

    fw::GameObject* pObject3 = new fw::GameObject(m_pGameCore, "Object 3", vec3(-4, 0, 0), getMesh("Square"), getMaterial("White"));
    pObject3->SetScale(vec3(0.5f, 20.0f, 0.5f));
    pObject3->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMidterm_WallLeft, LeftWallGroup, 0, true);
    m_Objects.push_back(pObject3);

    fw::GameObject* pObject4 = new fw::GameObject(m_pGameCore, "Object 4", vec3(4, 0, 0), getMesh("Square"), getMaterial("White"));
    pObject4->SetScale(vec3(0.5f, 20.0f, 0.5f));
    pObject4->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMidterm_WallRight, RightWallGroup, 0, true);
    m_Objects.push_back(pObject4);

    b2Vec2 anchorPos(pObject1->GetBody()->GetPosition());
    jointDefLeft.Initialize(pObject1->GetBody(), m_pPlayer->GetBody(), anchorPos);
    jointLeft = m_pWorld->CreateJoint(&jointDefLeft);

    m_ContactListener = new MidtermSceneContactListener();

    m_pWorld->SetContactListener(m_ContactListener);
}

MidtermScene::~MidtermScene()
{
    delete m_ContactListener;
}

void MidtermScene::Update(float deltaTime)
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
            if (jointLeft)
            {
                m_pWorld->DestroyJoint(jointLeft);
                jointLeft = nullptr;
            }
            else if (jointRight)
            {
                m_pWorld->DestroyJoint(jointRight);
                jointRight = nullptr;
            }
        }
    }

    if (leftwallHit && !jointLeft)
    {
        b2Vec2 anchorPosLeft(pObject1->GetBody()->GetPosition());
        jointDefLeft.Initialize(pObject1->GetBody(), m_pPlayer->GetBody(), anchorPosLeft);
        jointLeft = m_pWorld->CreateJoint(&jointDefLeft);
    }
    else
    {
        leftwallHit = false;
    }

    if (rightwallHit && !jointRight)
    {
        b2Vec2 anchorPosRight(pObject2->GetBody()->GetPosition());
        jointDefRight.Initialize(pObject2->GetBody(), m_pPlayer->GetBody(), anchorPosRight);
        jointRight = m_pWorld->CreateJoint(&jointDefRight);
    }
    else
    {
        rightwallHit = false;
    }

    m_pCamera->Update(deltaTime);

}

void MidtermScene::Draw()
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

void MidtermScene::OnEvent(fw::Event* pEvent)
{
}

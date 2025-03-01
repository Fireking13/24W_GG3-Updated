#include "Box2DScene.h"
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

Box2DScene::Box2DScene(Game* pGame)
    : Scene(pGame)
{
    m_Name = "Box2DTest";

	m_pCamera = new fw::Camera(m_pGameCore, vec3(0, 1, 0), vec3(0, 0, -25), vec3(0, 1, 0), vec3(0, 0, 3));

	m_pVirtualController = new VirtualController();

    m_pWorld = new b2World(b2Vec2(0, -10));

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>

    m_pPlayer = new Player(pGame, "Player", vec3(6, 5, 0), getMesh("Sprite"), getMaterial("MegaMan"));
    m_pPlayer->SetControler(m_pVirtualController);
    m_pPlayer->CreateBody(m_pWorld, true, Box2dShapes::Square, 0, 0, 0, false);
    m_Objects.push_back(m_pPlayer);

    fw::GameObject* pObject1 = new fw::GameObject(m_pGameCore, "Object 1", vec3(0, 0, 0), getMesh("Triangle"), getMaterial("VertexColor"));
    pObject1->CreateBody(m_pWorld, true, Box2dShapes::Triangle, 0 ,0, 0, false);
    m_Objects.push_back(pObject1);

    fw::GameObject* pObject2 = new fw::GameObject(m_pGameCore, "Object 2", vec3(10, 10, 0), getMesh("Triangle"), getMaterial("Blue"));
    pObject2->CreateBody(m_pWorld, true, Box2dShapes::Triangle, 0, 0, 0, false);
    m_Objects.push_back(pObject2);

    fw::GameObject* pObject3 = new fw::GameObject(m_pGameCore, "Object 3", vec3(5, 5, 0), getMesh("Square"), getMaterial("VertexColor"));
    pObject3->CreateBody(m_pWorld, true, Box2dShapes::Square, 0, 0, 0, false);
    m_Objects.push_back(pObject3);


    fw::GameObject* pObject4 = new fw::GameObject(m_pGameCore, "Object 4", vec3(1, 1, 0), getMesh("Square"), getMaterial("VertexColor"));
    pObject4->CreateBody(m_pWorld, true, Box2dShapes::Square, 0, 0, 0, false);
    m_Objects.push_back(pObject4);

    fw::GameObject* pObject5 = new fw::GameObject(m_pGameCore, "Object 5", vec3(1, 9, 0), getMesh("Square"), getMaterial("Blue"));
    pObject5->CreateBody(m_pWorld, true, Box2dShapes::Square, 0, 0, 0, false);
    m_Objects.push_back(pObject5);

    fw::GameObject* pObject7 = new fw::GameObject(m_pGameCore, "Object 7", vec3(6, 10, 0), getMesh("Circle"), getMaterial("Blue"));
    pObject7->CreateBody(m_pWorld, true, Box2dShapes::Circle, 0, 0, 0, false);
    m_Objects.push_back(pObject7);

    fw::GameObject* pObject8 = new fw::GameObject(m_pGameCore, "Object 8", vec3(9, 0, 0), getMesh("Square"), getMaterial("Blue"));
    pObject8->SetScale(vec3(9, 1, 1));
    pObject8->CreateBody(m_pWorld, false, Box2dShapes::Square, 0, 0, 0, false);
    m_Objects.push_back(pObject8);


    b2BodyDef bodyDef;
    b2Body* pGround = m_pWorld->CreateBody(&bodyDef);

    // Declare a joint definition object
    b2RevoluteJointDef jointDef;

    // Select a world space anchor point
    b2Vec2 anchorPos(5, 5);

    // Initialize the joint definition with the 2 bodies and the world space anchor
    jointDef.Initialize(pGround, m_pPlayer->GetBody(), anchorPos);


    b2PrismaticJointDef motorJointDef;

    // Select a world space anchor point for the motor
    b2Vec2 motorAnchorPos(5, 5);

    // Initialize the joint definition with the 2 bodies and the world space anchor
    motorJointDef.Initialize(pGround, pObject3->GetBody(), motorAnchorPos, b2Vec2(0, 1)); // Move Object 3 vertically

    // Enable the motor for the joint
    motorJointDef.enableMotor = true;

    // Set the motor speed and maximum motor force
    motorJointDef.motorSpeed = 10.0f; // Motor speed in units per second (positive value moves Object 3 upwards)
    motorJointDef.maxMotorForce = 100.0f; // Maximum force in Newtons

    // Create the actual joint in the world
    b2PrismaticJoint* pMotorJoint = (b2PrismaticJoint*)m_pWorld->CreateJoint(&motorJointDef);
}

Box2DScene::~Box2DScene()
{
}

void Box2DScene::Update(float deltaTime)
{

    m_pWorld->Step(1 / 60.0f, 8, 3);

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    m_pCamera->Update(deltaTime);

}

void Box2DScene::Draw()
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

void Box2DScene::OnEvent(fw::Event* pEvent)
{
}

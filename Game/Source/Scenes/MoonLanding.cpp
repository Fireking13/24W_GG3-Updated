#include "MoonLanding.h"
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
#include "math.h"

MoonLandingScene::MoonLandingScene(Game* pGame)
    : Scene(pGame)
{
    m_Game = pGame;

    m_Name = "MoonLanding";

    m_pCamera = new fw::Camera(m_pGameCore, vec3(0, 0, 0), vec3(0, 0, -25), vec3(0, 1, 0), vec3(0, 0, 0));

    m_pVirtualController = new VirtualController();

    m_pWorld = new b2World(b2Vec2(0, -0.5));

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>


    b2BodyDef bodyDef;
    pGround = m_pWorld->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;

    PlayerGroup = PhysicsCategoriesMoonLanding_Ground | PhysicsCategoriesMoonLanding_LandingPad;
    GroundGroup = PhysicsCategoriesMoonLanding_Ground | PhysicsCategoriesMoonLanding_Player | PhysicsCategoriesMoonLanding_Leg | PhysicsCategoriesMoonLanding_LandingPad;
    LandingPadGroup = PhysicsCategoriesMoonLanding_Ground | PhysicsCategoriesMoonLanding_Player | PhysicsCategoriesMoonLanding_Leg | PhysicsCategoriesMoonLanding_LandingPad;
    LegGroup = PhysicsCategoriesMoonLanding_Ground | PhysicsCategoriesMoonLanding_LandingPad;
    FireGroup = PhysicsCategoriesMoonLanding_None;

    /*
    fw::GameObject* pTest = new fw::GameObject(m_pGameCore, "LeftThuster", vec3(3, 8, 0), getMesh("Square"), getMaterial("Blue"));
    pTest->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Fire, FireGroup, 0, false);
    m_Objects.push_back(pTest);
    */ //for debuging

    m_pPlayer = new Player(pGame, "Player", vec3(0, 8, 0), getMesh("ShipHull"), getMaterial("Ship"));
    m_pPlayer->SetScale(vec3(0.5f, 0.75f, 1));
    m_pPlayer->SetControler(m_pVirtualController);
    m_pPlayer->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Player, PlayerGroup, 0, false);
    m_Objects.push_back(m_pPlayer);

    pLeftThuster = new fw::GameObject(m_pGameCore, "LeftThuster", vec3(-0.5 + 0.125f, 7.75 + 0.125, 0), getMesh("ShipThruster"), getMaterial("Ship"));
    pLeftThuster->SetScale(vec3(0.25f, 0.5f, 1));
    pLeftThuster->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Player, PlayerGroup, 0, false);
    m_Objects.push_back(pLeftThuster);

    pRightThuster = new fw::GameObject(m_pGameCore, "RightThuster", vec3(0.5 - 0.125f, 7.75 + 0.125, 0), getMesh("ShipThruster"), getMaterial("Ship"));
    pRightThuster->SetScale(vec3(0.25f, 0.5f, 1));
    pRightThuster->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Player, PlayerGroup, 0, false);
    m_Objects.push_back(pRightThuster);

    pLeftFire = new fw::GameObject(m_pGameCore, "LeftFire", vec3(-0.5 + 0.125f, 7.5, 0), getMesh("ShipFire"), getMaterial("Ship"));
    pLeftFire->SetScale(vec3(0.25f, 0.25f, 1));
    pLeftFire->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Fire, PlayerGroup, 0, false);
    m_Objects.push_back(pLeftFire);

    pRightFire = new fw::GameObject(m_pGameCore, "RightFire", vec3(0.5 - 0.125f, 7.5, 0), getMesh("ShipFire"), getMaterial("Ship"));
    pRightFire->SetScale(vec3(0.25f, 0.25f, 1));
    pRightFire->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Fire, PlayerGroup, 0, false);
    m_Objects.push_back(pRightFire);

    pLeftLeg = new fw::GameObject(m_pGameCore, "LeftLeg", vec3(-0.25, 7.5, 0), getMesh("ShipLeg"), getMaterial("Ship"));
    pLeftLeg->SetScale(vec3(0.125f, 0.25f, 1));
    pLeftLeg->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Leg, LegGroup, 0, false);
    m_Objects.push_back(pLeftLeg);

    pRightLeg = new fw::GameObject(m_pGameCore, "RightLeg", vec3(0.25, 7.5, 0), getMesh("ShipLeg"), getMaterial("Ship"));
    pRightLeg->SetScale(vec3(0.125f, 0.25f, 1));
    pRightLeg->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Leg, LegGroup, 0, false);
    m_Objects.push_back(pRightLeg);


    pivotLeft = b2Vec2(-0.5 + 0.25f, 7.75 + 0.125);
    pivotRight = b2Vec2(0.5 - 0.25f, 7.75 + 0.125);
    pivotLeftFire = b2Vec2(-0.5 + 0.25f, 7.5 + 0.125f);
    pivotRightFire = b2Vec2(0.5 - 0.25f, 7.5 + 0.125f);
    pivotLeftLeg = b2Vec2(-0.25f + 0.1f, 7.5 + 0.125f);
    pivotRightLeg = b2Vec2(0.25f - 0.1f, 7.5 + 0.125f);

    leftWeldJointDef.Initialize(m_pPlayer->GetBody(), pLeftThuster->GetBody(), pivotLeft);
    rightWeldJointDef.Initialize(m_pPlayer->GetBody(), pRightThuster->GetBody(), pivotRight);

    leftLegWeldJointDef.Initialize(m_pPlayer->GetBody(), pLeftLeg->GetBody(), pivotLeftLeg);
    rightLegWeldJointDef.Initialize(m_pPlayer->GetBody(), pRightLeg->GetBody(), pivotRightLeg);

    leftFireWeldJointDef.Initialize(pLeftThuster->GetBody(), pLeftFire->GetBody(), pivotLeftFire);
    rightFireWeldJointDef.Initialize(pRightThuster->GetBody(), pRightFire->GetBody(), pivotRightFire);

    leftWeldJoint = m_pWorld->CreateJoint(&leftWeldJointDef);
    rightWeldJoint = m_pWorld->CreateJoint(&rightWeldJointDef);
    leftLegWeldJoint = m_pWorld->CreateJoint(&leftLegWeldJointDef);
    rightLegWeldJoint = m_pWorld->CreateJoint(&rightLegWeldJointDef);
    leftFireWeldJoint = m_pWorld->CreateJoint(&leftFireWeldJointDef);
    rightFireWeldJoint = m_pWorld->CreateJoint(&rightFireWeldJointDef);

    fw::GameObject* pFloor = new fw::GameObject(m_pGameCore, "Floor", vec3(0, -4 - 15, 0), getMesh("Square"), getMaterial("White"));
    pFloor->SetScale(vec3(40, 7, 1));
    pFloor->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Ground, GroundGroup, 0, false);
    m_Objects.push_back(pFloor);

    fw::GameObject* pLandingPad1 = new fw::GameObject(m_pGameCore, "LandingPad1", vec3(0, 0 - 15, 0), getMesh("Square"), getMaterial("Red"));
    pLandingPad1->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMoonLanding_LandingPad, LandingPadGroup, 0, false);
    m_Objects.push_back(pLandingPad1);

    fw::GameObject* pLandingPad2 = new fw::GameObject(m_pGameCore, "LandingPad2", vec3(10, 0 - 15, 0), getMesh("Square"), getMaterial("Red"));
    pLandingPad2->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMoonLanding_LandingPad, LandingPadGroup, 0, false);
    m_Objects.push_back(pLandingPad2);

    fw::GameObject* pLandingPad3 = new fw::GameObject(m_pGameCore, "LandingPad3", vec3(-10, 0 - 15, 0), getMesh("Square"), getMaterial("Red"));
    pLandingPad3->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMoonLanding_LandingPad, LandingPadGroup, 0, false);
    m_Objects.push_back(pLandingPad3);

    m_LandingPadList.push_back(pLandingPad1);
    m_LandingPadList.push_back(pLandingPad2);
    m_LandingPadList.push_back(pLandingPad3);

    for (int i = -20; i < 20; i++)
    {
        if (i != 0 && i != 10 && i != -10)
        {
            fw::GameObject* pObject = new fw::GameObject(m_pGameCore, "Rock", vec3(float(i), -0.5 - 15, 0), getMesh("Square"), getMaterial("White"));
            pObject->SetRotation(vec3(0, 0, -45));
            pObject->SetScale(vec3(1, 1, 1));
            pObject->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Ground, GroundGroup, 0, false);
            m_Objects.push_back(pObject);
        }
    }



    minZoom = m_pCamera->GetPosition().z - 10;
    maxZoom = 15;

    leftLegOn = false;
    rightLegOn = false;

    hasLanded = false;
    hasCrashed = false;

    missionSupportText = std::string(" ");

    angularDamping = 8.0f;

    m_pPlayer->GetBody()->SetAngularDamping(angularDamping);
    pLeftThuster->GetBody()->SetAngularDamping(angularDamping);
    pRightThuster->GetBody()->SetAngularDamping(angularDamping);
    pLeftFire->GetBody()->SetAngularDamping(angularDamping);
    pRightFire->GetBody()->SetAngularDamping(angularDamping);
    pLeftLeg->GetBody()->SetAngularDamping(angularDamping);
    pRightLeg->GetBody()->SetAngularDamping(angularDamping);


    m_ContactListener = new MoonLandingContactListener(pGame);
    m_pWorld->SetContactListener(m_ContactListener);


}

MoonLandingScene::~MoonLandingScene()
{
    delete m_ContactListener;
}

void MoonLandingScene::Update(float deltaTime)
{
#define getMaterial m_Game->GetResources()->Get<fw::Material>

    m_pWorld->Step(1 / 60.0f, 8, 3);

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    if (m_pVirtualController != nullptr)
    {
        if (!hasLanded && !hasCrashed)
        {
            if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Left))
            {
                pLeftFire->SetMaterial(getMaterial("ShipLit"));
                b2Vec2 force(0.0f, 0.5f);
                force = b2Mul(b2Rot(pLeftThuster->GetBody()->GetAngle()), force);
                pLeftThuster->GetBody()->ApplyForceToCenter(force, true);
            }
            if (m_pVirtualController->IsActionReleased(VirtualController::Actions::Left))
            {
                pLeftFire->SetMaterial(getMaterial("Ship"));
            }

            if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Right))
            {
                pRightFire->SetMaterial(getMaterial("ShipLit"));
                b2Vec2 force(0.0f, 0.5f);
                force = b2Mul(b2Rot(pRightThuster->GetBody()->GetAngle()), force);
                pRightThuster->GetBody()->ApplyForceToCenter(force, true);
            }
            if (m_pVirtualController->IsActionReleased(VirtualController::Actions::Right))
            {
                pRightFire->SetMaterial(getMaterial("Ship"));
            }
        }
        else
        {
            pLeftFire->SetMaterial(getMaterial("Ship"));
            pRightFire->SetMaterial(getMaterial("Ship"));
        }

        if (m_pVirtualController->IsActionPressed(VirtualController::Actions::Reset))
        {
            m_pWorld->DestroyJoint(leftWeldJoint);
            m_pWorld->DestroyJoint(rightWeldJoint);
            m_pWorld->DestroyJoint(leftLegWeldJoint);
            m_pWorld->DestroyJoint(rightLegWeldJoint);
            m_pWorld->DestroyJoint(leftFireWeldJoint);
            m_pWorld->DestroyJoint(rightFireWeldJoint);

            m_pWorld->DestroyBody(m_pPlayer->GetBody());
            m_pWorld->DestroyBody(pLeftThuster->GetBody());
            m_pWorld->DestroyBody(pRightThuster->GetBody());
            m_pWorld->DestroyBody(pLeftFire->GetBody());
            m_pWorld->DestroyBody(pRightFire->GetBody());
            m_pWorld->DestroyBody(pLeftLeg->GetBody());
            m_pWorld->DestroyBody(pRightLeg->GetBody());

            m_pPlayer->RemoveBody();
            pLeftThuster->RemoveBody();
            pRightThuster->RemoveBody();
            pLeftFire->RemoveBody();
            pRightFire->RemoveBody();
            pLeftLeg->RemoveBody();
            pRightLeg->RemoveBody();

            // Reset player position and rotation
            m_pPlayer->SetPosition(vec3(0, 8, 0));
            m_pPlayer->SetRotation(vec3(0, 0, 0));

            // Reset other objects positions and rotations
            pLeftThuster->SetPosition(vec3(-0.5 + 0.125f, 7.75 + 0.125, 0));
            pRightThuster->SetPosition(vec3(0.5 - 0.125f, 7.75 + 0.125, 0));
            pLeftFire->SetPosition(vec3(-0.5 + 0.125f, 7.5, 0));
            pRightFire->SetPosition(vec3(0.5 - 0.125f, 7.5, 0));
            pLeftLeg->SetPosition(vec3(-0.25, 7.5, 0));
            pRightLeg->SetPosition(vec3(0.25, 7.5, 0));

            pLeftThuster->SetRotation(vec3(0, 0, 0));
            pRightThuster->SetRotation(vec3(0, 0, 0));
            pLeftFire->SetRotation(vec3(0, 0, 0));
            pRightFire->SetRotation(vec3(0, 0, 0));
            pLeftLeg->SetRotation(vec3(0, 0, 0));
            pRightLeg->SetRotation(vec3(0, 0, 0));

            // Recreate bodies and joints
            m_pPlayer->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Player, PlayerGroup, 0, false);
            pLeftThuster->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Player, PlayerGroup, 0, false);
            pRightThuster->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Player, PlayerGroup, 0, false);
            pLeftFire->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Fire, FireGroup, 0, false);
            pRightFire->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Fire, FireGroup, 0, false);
            pLeftLeg->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Leg, LegGroup, 0, false);
            pRightLeg->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategoriesMoonLanding_Leg, LegGroup, 0, false);


            leftWeldJointDef.Initialize(m_pPlayer->GetBody(), pLeftThuster->GetBody(), pivotLeft);
            rightWeldJointDef.Initialize(m_pPlayer->GetBody(), pRightThuster->GetBody(), pivotRight);

            leftLegWeldJointDef.Initialize(m_pPlayer->GetBody(), pLeftLeg->GetBody(), pivotLeftLeg);
            rightLegWeldJointDef.Initialize(m_pPlayer->GetBody(), pRightLeg->GetBody(), pivotRightLeg);

            leftFireWeldJointDef.Initialize(pLeftThuster->GetBody(), pLeftFire->GetBody(), pivotLeftFire);
            rightFireWeldJointDef.Initialize(pRightThuster->GetBody(), pRightFire->GetBody(), pivotRightFire);


            leftWeldJoint = m_pWorld->CreateJoint(&leftWeldJointDef);
            rightWeldJoint = m_pWorld->CreateJoint(&rightWeldJointDef);
            leftLegWeldJoint = m_pWorld->CreateJoint(&leftLegWeldJointDef);
            rightLegWeldJoint = m_pWorld->CreateJoint(&rightLegWeldJointDef);
            leftFireWeldJoint = m_pWorld->CreateJoint(&leftFireWeldJointDef);
            rightFireWeldJoint = m_pWorld->CreateJoint(&rightFireWeldJointDef);


            m_pPlayer->GetBody()->SetAngularDamping(angularDamping);
            pLeftThuster->GetBody()->SetAngularDamping(angularDamping);
            pRightThuster->GetBody()->SetAngularDamping(angularDamping);
            pLeftFire->GetBody()->SetAngularDamping(angularDamping);
            pRightFire->GetBody()->SetAngularDamping(angularDamping);
            pLeftLeg->GetBody()->SetAngularDamping(angularDamping);
            pRightLeg->GetBody()->SetAngularDamping(angularDamping);

            leftLegOn = false;
            rightLegOn = false;

            hasLanded = false;
            hasCrashed = false;

            missionSupportText = std::string("");
        }
    }

    //set cameras poition to the player
    float test = m_pPlayer->GetPosition().y;
    float test2 = m_pPlayer->GetPosition().x;

    float zoom = minZoom;

    float deltaX = m_pPlayer->GetPosition().x - m_LandingPadList[0]->GetPosition().x;
    float deltaY = m_pPlayer->GetPosition().y - m_LandingPadList[0]->GetPosition().y;

    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    for (int i = 0; i < m_LandingPadList.size(); i++)
    {
        float deltaX = m_pPlayer->GetPosition().x - m_LandingPadList[i]->GetPosition().x;
        float deltaY = m_pPlayer->GetPosition().y - m_LandingPadList[i]->GetPosition().y;

        float newDistance = sqrt(deltaX * deltaX + deltaY * deltaY);

        if (newDistance < distance)
        {
            distance = newDistance;
        }
    }

    if (distance < 15)
    {
        float zoomFactor = 1.f - (distance / 15.0f); // Calculate zoom factor based on distance

        zoom = minZoom + (zoomFactor * (maxZoom - minZoom)); // Apply zoom factor to adjust zoom level

        // Ensure zoom stays within bounds
        if (zoom > maxZoom)
        {
            zoom = maxZoom;
        }
        else if (zoom < minZoom)
        {
            zoom = minZoom;
        }
    }
    else
    {
        zoom = minZoom;
    }

    b2Vec2 playerSpeed = m_pPlayer->GetBody()->GetLinearVelocity();
    float speed = playerSpeed.Length();

    if (leftLegOn && rightLegOn && !hasCrashed && !hasLanded && speed == 0) //
    {
        hasLanded = true;

        missionSupportText = std::string("Message: Well done, another happy landing.");
    }

    if (!hasCrashed)
    {
        float angle = fmod(m_pPlayer->GetBody()->GetAngle(), 2 * b2_pi);

        if (angle < 0)
        {
            angle += 2 * b2_pi;
        }

        if (speed > 3.0f && angle > b2_pi / 4.0f && angle < (7 * b2_pi) / 4.0f)
        {
            missionSupportText = std::string("Message: You are going too fast and at a wrong angle!");
        }
        else if (speed > 3.0f)
        {
            missionSupportText = std::string("Message: You are going too fast!");
        }
        else if (angle > b2_pi / 4.0f && angle < (7 * b2_pi) / 4.0f)
        {
            missionSupportText = std::string("Message: You are at a wrong angle!");
        }
        else if (!hasLanded)
        {
            missionSupportText = std::string("");
        }
    }
    else
    {
        missionSupportText = std::string("Message: You crashed it! How did you even get this job!");
    }

    m_Game->Editor_DisplayCustomPopUp(std::string("Mission Controll"), missionSupportText);

    m_pCamera->SetPosition(vec3(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, zoom));
    m_pCamera->Update(deltaTime);

}

void MoonLandingScene::Draw()
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

void MoonLandingScene::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == ColisionGameEvent::GetStaticEventType())
    {
        ColisionGameEvent* pColEvent = static_cast<ColisionGameEvent*>(pEvent);

        fw::GameObject* pObjectA = (fw::GameObject*)(pColEvent->GetFixtureA()->GetBody()->GetUserData().pointer);
        fw::GameObject* pObjectB = (fw::GameObject*)(pColEvent->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (IsLeg(pColEvent->GetFixtureA()) && IsPad(pColEvent->GetFixtureB()))
        {
            if (pObjectA == pLeftLeg) //due to logic gates made in the if statment in update about landing, its imposable to land with out both legs touching even if they come off the ground its fine and if the main body touches it crashes anyways 
            {
                leftLegOn = true;
            }
            if (pObjectA == pRightLeg)
            {
                rightLegOn = true;
            }
        }

        if (IsPlayer(pColEvent->GetFixtureA()) || IsLeg(pColEvent->GetFixtureA()) && IsGround(pColEvent->GetFixtureB()))
        {
            hasCrashed = true;
        }
        else if (IsPlayer(pColEvent->GetFixtureA()) && IsPad(pColEvent->GetFixtureB()))
        {
            hasCrashed = true;
        }
    }
}

bool MoonLandingScene::IsLeg(b2Fixture* fixture)
{
    return fixture->GetFilterData().categoryBits == PhysicsCategoriesMoonLanding_Leg;
}

bool MoonLandingScene::IsPad(b2Fixture* fixture)
{
    return fixture->GetFilterData().categoryBits == PhysicsCategoriesMoonLanding_LandingPad;
}

bool MoonLandingScene::IsGround(b2Fixture* fixture)
{
    return fixture->GetFilterData().categoryBits == PhysicsCategoriesMoonLanding_Ground;
}

bool MoonLandingScene::IsPlayer(b2Fixture* fixture)
{
    return fixture->GetFilterData().categoryBits == PhysicsCategoriesMoonLanding_Player;
}



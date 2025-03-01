#include "PinBallScene.h"
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


PinBallScene::PinBallScene(Game* pGame)
    : Scene(pGame)
{

    m_Name = "PinBallTest";

    m_pCamera = new fw::Camera(m_pGameCore, vec3(0, 1, 0), vec3(0, -15, -15), vec3(0, 1, 0), vec3(0, 0, 3));
    m_pCamera->SetRotation(vec3(0,0,0));

	m_pVirtualController = new VirtualController();

    m_pWorld = new b2World(b2Vec2(0, -10));

#define getMesh pGame->GetResources()->Get<fw::Mesh>
#define getMaterial pGame->GetResources()->Get<fw::Material>


    b2BodyDef bodyDef;
    b2Body* pGround = m_pWorld->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;

    //groups: red, green, blue, walls, floor, padels, bumber
    uint16 blueGroup = PhysicsCategory_Wall | PhysicsCategory_Padel | PhysicsCategory_Floor | PhysicsCategory_Blue | PhysicsCategory_Bumper;
    uint16 redGroup = PhysicsCategory_Wall | PhysicsCategory_Padel | PhysicsCategory_Floor | PhysicsCategory_Red | PhysicsCategory_Bumper;
    uint16 greenGroup = PhysicsCategory_Wall | PhysicsCategory_Padel | PhysicsCategory_Floor | PhysicsCategory_Green | PhysicsCategory_Bumper;
    uint16 floorGroup = PhysicsCategory_Wall | PhysicsCategory_Floor | PhysicsCategory_Green | PhysicsCategory_Red | PhysicsCategory_Blue | PhysicsCategory_Padel;
    uint16 wallGroup = PhysicsCategory_Wall | PhysicsCategory_Floor | PhysicsCategory_Green | PhysicsCategory_Red | PhysicsCategory_Blue;
    uint16 padelGroup = PhysicsCategory_Padel | PhysicsCategory_Green | PhysicsCategory_Red | PhysicsCategory_Blue | PhysicsCategory_Padel;
    uint16 bumperGroup = PhysicsCategory_Green | PhysicsCategory_Red | PhysicsCategory_Blue | PhysicsCategory_Bumper;

    //blue
    fw::GameObject* pBlueBall = new fw::GameObject(m_pGameCore, "Blue Ball", vec3(-11.5f, 2, 0), getMesh("Circle"), getMaterial("Blue"));
    pBlueBall->SetScale(vec3(0.5f, 0.5f, 0.5f));
    pBlueBall->CreateBody(m_pWorld, true, Box2dShapes::Circle, PhysicsCategory_Blue, blueGroup, 0.5f, false);
    m_Objects.push_back(pBlueBall);

    fw::GameObject* pBlueHoldBoxC = new fw::GameObject(m_pGameCore, "BlueHoldBoxCenter", vec3(5, 4, 0), getMesh("Square"), getMaterial("Blue"));
    pBlueHoldBoxC->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Blue, blueGroup, 0, false);
    m_Objects.push_back(pBlueHoldBoxC);

    fw::GameObject* pBlueHoldBoxL = new fw::GameObject(m_pGameCore, "BlueHoldBoxLeft", vec3(4, 4, 0), getMesh("RightTriangleFliped"), getMaterial("Blue"));
    pBlueHoldBoxL->SetRotation(vec3(0, 0, -90));
    pBlueHoldBoxL->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Blue, blueGroup, 0, false);
    m_Objects.push_back(pBlueHoldBoxL);

    fw::GameObject* pBlueHoldBoxLU = new fw::GameObject(m_pGameCore, "BlueHoldBoxLeftUp", vec3(4, 5, 0), getMesh("RightTriangle"), getMaterial("Blue"));
    pBlueHoldBoxLU->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Blue, blueGroup, 0, false);
    m_Objects.push_back(pBlueHoldBoxLU);

    fw::GameObject* pBlueHoldBoxR = new fw::GameObject(m_pGameCore, "BlueHoldBoxRight", vec3(6, 4, 0), getMesh("RightTriangle"), getMaterial("Blue"));
    pBlueHoldBoxR->SetRotation(vec3(0, 0, 90));
    pBlueHoldBoxR->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Blue, blueGroup, 0, false);
    m_Objects.push_back(pBlueHoldBoxR);

    fw::GameObject* pBlueHoldBoxRU = new fw::GameObject(m_pGameCore, "BlueHoldBoxRightUp", vec3(6, 5, 0), getMesh("RightTriangleFliped"), getMaterial("Blue"));
    pBlueHoldBoxRU->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Blue, blueGroup, 0, false);
    m_Objects.push_back(pBlueHoldBoxRU);

    fw::GameObject* pBlueHoldBoxOB = new fw::GameObject(m_pGameCore, "BlueHoldBoxObstical", vec3(3, 8.5f, 0), getMesh("Square"), getMaterial("Blue"));
    pBlueHoldBoxOB->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategory_Blue, blueGroup, 0, false);
    m_Objects.push_back(pBlueHoldBoxOB);

    b2RevoluteJointDef blueJointDef; //this is the blue box obstical swing point
    b2Vec2 anchorPosBlueOB(5, 8.5f);
    blueJointDef.Initialize(pGround, pBlueHoldBoxOB->GetBody(), anchorPosBlueOB);
    m_pWorld->CreateJoint(&blueJointDef);


    //red
    fw::GameObject* pRedBall = new fw::GameObject(m_pGameCore, "Red Ball", vec3(11.5f, 2, 0), getMesh("Circle"), getMaterial("Red"));
    pRedBall->SetScale(vec3(0.5f, 0.5f, 0.5f));
    pRedBall->CreateBody(m_pWorld, true, Box2dShapes::Circle, PhysicsCategory_Red, redGroup, 0.5f, false);
    m_Objects.push_back(pRedBall);

    fw::GameObject* pRedHoldBoxC = new fw::GameObject(m_pGameCore, "RedHoldBoxCenter", vec3(-6, 0, 0), getMesh("Square"), getMaterial("Red"));
    pRedHoldBoxC->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Red, redGroup, 0, false);
    m_Objects.push_back(pRedHoldBoxC);

    fw::GameObject* pRedHoldBoxL = new fw::GameObject(m_pGameCore, "RedHoldBoxLeft", vec3(-7, 0, 0), getMesh("RightTriangleFliped"), getMaterial("Red"));
    pRedHoldBoxL->SetRotation(vec3(0, 0, -90));
    pRedHoldBoxL->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Red, redGroup, 0, false);
    m_Objects.push_back(pRedHoldBoxL);

    fw::GameObject* pRedHoldBoxLU = new fw::GameObject(m_pGameCore, "RedHoldBoxLeftUp", vec3(-7, 1, 0), getMesh("RightTriangle"), getMaterial("Red"));
    pRedHoldBoxLU->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Red, redGroup, 0, false);
    m_Objects.push_back(pRedHoldBoxLU);

    fw::GameObject* pRedHoldBoxR = new fw::GameObject(m_pGameCore, "RedHoldBoxRight", vec3(-5, 0, 0), getMesh("RightTriangle"), getMaterial("Red"));
    pRedHoldBoxR->SetRotation(vec3(0, 0, 90));
    pRedHoldBoxR->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Red, redGroup, 0, false);
    m_Objects.push_back(pRedHoldBoxR);

    fw::GameObject* pRedHoldBoxRU = new fw::GameObject(m_pGameCore, "RedHoldBoxRightUp", vec3(-5, 1, 0), getMesh("RightTriangleFliped"), getMaterial("Red"));
    pRedHoldBoxRU->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Red, redGroup, 0, false);
    m_Objects.push_back(pRedHoldBoxRU);

    fw::GameObject* pRedHoldBoxOB = new fw::GameObject(m_pGameCore, "RedHoldBoxObstical", vec3(-8, 5, 0), getMesh("Square"), getMaterial("Red"));
    pRedHoldBoxOB->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategory_Red, redGroup, 0, false);
    m_Objects.push_back(pRedHoldBoxOB);

    b2RevoluteJointDef redJointDef; //this is the reb box obstical swing point
    b2Vec2 anchorPosRedOB(-6, 5);
    redJointDef.Initialize(pGround, pRedHoldBoxOB->GetBody(), anchorPosRedOB);
    m_pWorld->CreateJoint(&redJointDef);


    //green
    fw::GameObject* pGreenBall = new fw::GameObject(m_pGameCore, "Green Ball", vec3(-11.5f, 3, 0), getMesh("Circle"), getMaterial("Green"));
    pGreenBall->SetScale(vec3(0.5f, 0.5f, 0.5f));
    pGreenBall->CreateBody(m_pWorld, true, Box2dShapes::Circle, PhysicsCategory_Green, greenGroup, 0.5f, false);
    m_Objects.push_back(pGreenBall);

    fw::GameObject* pGreenHoldBoxC = new fw::GameObject(m_pGameCore, "GreenHoldBoxCenter", vec3(-1, 6, 0), getMesh("Square"), getMaterial("Green"));
    pGreenHoldBoxC->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxC);

    fw::GameObject* pGreenHoldBoxL = new fw::GameObject(m_pGameCore, "GreenHoldBoxLeft", vec3(-2, 6, 0), getMesh("RightTriangleFliped"), getMaterial("Green"));
    pGreenHoldBoxL->SetRotation(vec3(0, 0, -90));
    pGreenHoldBoxL->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxL);

    fw::GameObject* pGreenHoldBoxLU = new fw::GameObject(m_pGameCore, "GreenHoldBoxLeftUp", vec3(-2, 7, 0), getMesh("RightTriangle"), getMaterial("Green"));
    pGreenHoldBoxLU->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxLU);

    fw::GameObject* pGreenHoldBoxR = new fw::GameObject(m_pGameCore, "GreenHoldBoxRight", vec3(0, 6, 0), getMesh("RightTriangle"), getMaterial("Green"));
    pGreenHoldBoxR->SetRotation(vec3(0, 0, 90));
    pGreenHoldBoxR->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxR);

    fw::GameObject* pGreenHoldBoxRU = new fw::GameObject(m_pGameCore, "GreenHoldBoxRightUp", vec3(0, 7, 0), getMesh("RightTriangleFliped"), getMaterial("Green"));
    pGreenHoldBoxRU->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxRU);

    fw::GameObject* pGreenHoldBoxOBc= new fw::GameObject(m_pGameCore, "GreenHoldBoxObsticalCenter", vec3(0, 9.5f, 0), getMesh("Square"), getMaterial("Green"));
    pGreenHoldBoxOBc->SetScale(vec3(10, 1, 1));
    pGreenHoldBoxOBc->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxOBc);

    fw::GameObject* pGreenHoldBoxOBl = new fw::GameObject(m_pGameCore, "GreenHoldBoxObsticalLeft", vec3(-4.5, 8.5f, 0), getMesh("RightTriangle"), getMaterial("Green"));
    pGreenHoldBoxOBl->SetRotation(vec3(0, 0, 90));
    pGreenHoldBoxOBl->CreateBody(m_pWorld, true, Box2dShapes::RightTriangle, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxOBl);

    fw::GameObject* pGreenHoldBoxOBr = new fw::GameObject(m_pGameCore, "GreenHoldBoxObsticalRight", vec3(4.5, 8.5f, 0), getMesh("RightTriangleFliped"), getMaterial("Green"));
    pGreenHoldBoxOBr->SetRotation(vec3(0, 0, -90));
    pGreenHoldBoxOBr->CreateBody(m_pWorld, true, Box2dShapes::RightTriangleFliped, PhysicsCategory_Green, greenGroup, 0, false);
    m_Objects.push_back(pGreenHoldBoxOBr);

    b2Vec2 pivotLeft(0, 0);     // Pivot for the left triangle //this is the welding of the triangels to the green bar
    b2Vec2 pivotRight(0, 0);    // Pivot for the right triangle
    b2WeldJointDef leftWeldJointDef, rightWeldJointDef;
    leftWeldJointDef.Initialize(pGreenHoldBoxOBc->GetBody(), pGreenHoldBoxOBl->GetBody(), pivotLeft);
    rightWeldJointDef.Initialize(pGreenHoldBoxOBc->GetBody(), pGreenHoldBoxOBr->GetBody(), pivotRight);
    m_pWorld->CreateJoint(&leftWeldJointDef);
    m_pWorld->CreateJoint(&rightWeldJointDef);

    b2Vec2 axis(1.0f, 0.0f);    //this is the anchor and movement for the green bar
    b2Vec2 anchorPosGreenOB(0, 9.5f);
    greenBarJointDef.Initialize(pGround, pGreenHoldBoxOBc->GetBody(), anchorPosGreenOB, axis);
    greenBarJointDef.enableLimit = true;
    greenBarJointDef.lowerTranslation = -6.5f;
    greenBarJointDef.upperTranslation = 6.5f;
    greenBarJointDef.enableMotor = true;
    greenBarJointDef.maxMotorForce = 100.0f;
    greenBarJointDef.motorSpeed = 75.0f;
    greenBarJoint = (b2PrismaticJoint*)m_pWorld->CreateJoint(&greenBarJointDef);


    //floor
    fw::GameObject* pFloor = new fw::GameObject(m_pGameCore, "Floor", vec3(0, -9, 0), getMesh("Square"), getMaterial("Cyan"));
    pFloor->SetScale(vec3(25, 1, 1));
    pFloor->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Floor, floorGroup, 0, false);
    m_Objects.push_back(pFloor);


    //walls
    fw::GameObject* pLeftWall = new fw::GameObject(m_pGameCore, "LeftWall", vec3( -11.5f, -4, 0), getMesh("Square"), getMaterial("White"));
    pLeftWall->SetScale(vec3(2, 9, 1));
    pLeftWall->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pLeftWall);

    fw::GameObject* pRightWall = new fw::GameObject(m_pGameCore, "RightWall", vec3(11.5f, -4, 0), getMesh("Square"), getMaterial("White"));
    pRightWall->SetScale(vec3(2, 9, 1));
    pRightWall->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pRightWall);

    fw::GameObject* pRoof = new fw::GameObject(m_pGameCore, "Roof", vec3(0, 11, 0), getMesh("Square"), getMaterial("White"));
    pRoof->SetScale(vec3(29, 1, 1));
    pRoof->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pRoof);

    fw::GameObject* pLeftWallUp = new fw::GameObject(m_pGameCore, "LeftWallUp", vec3(-13.5f, 5, 0), getMesh("Square"), getMaterial("White"));
    pLeftWallUp->SetScale(vec3(2, 11, 1));
    pLeftWallUp->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pLeftWallUp);

    fw::GameObject* pRightWallUp = new fw::GameObject(m_pGameCore, "RightWallUp", vec3(13.5f, 5, 0), getMesh("Square"), getMaterial("White"));
    pRightWallUp->SetScale(vec3(2, 11, 1));
    pRightWallUp->CreateBody(m_pWorld, false, Box2dShapes::Square, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pRightWallUp);

    fw::GameObject* pSloopLeft = new fw::GameObject(m_pGameCore, "LeftSloop", vec3(-11.5f, 1, 0), getMesh("RightTriangle"), getMaterial("White"));
    pSloopLeft->SetScale(vec3(2, 1, 1));
    pSloopLeft->CreateBody(m_pWorld, false, Box2dShapes::RightTriangle, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pSloopLeft);
    
    fw::GameObject* pSloopRight = new fw::GameObject(m_pGameCore, "RightSloop", vec3(11.5f, 1, 0), getMesh("RightTriangleFliped"), getMaterial("White"));
    pSloopRight->SetScale(vec3(2, 1, 1));
    pSloopRight->CreateBody(m_pWorld, false, Box2dShapes::RightTriangleFliped, PhysicsCategory_Wall, wallGroup, 0, false);
    m_Objects.push_back(pSloopRight);


    //bumbper
    fw::GameObject* pBumperArm = new fw::GameObject(m_pGameCore, "BumperArm", vec3(0, 0, 0), getMesh("Square"), getMaterial("White"));
    pBumperArm->SetScale(vec3(0.5f, 2, 1));
    pBumperArm->CreateBody(m_pWorld, true, Box2dShapes::Square, PhysicsCategory_Bumper, bumperGroup, 0, false);
    m_Objects.push_back(pBumperArm);

    fw::GameObject* pBumper = new fw::GameObject(m_pGameCore, "Bumper", vec3(0, -1, 0), getMesh("Circle"), getMaterial("White"));
    pBumper->CreateBody(m_pWorld, true, Box2dShapes::Circle, PhysicsCategory_Bumper, bumperGroup, 0, false);
    m_Objects.push_back(pBumper);

    b2Vec2 ballToArmJoint(0, 0); //this is the bumber ball head being welded to the arm of the bumber
    b2WeldJointDef ballToArmJointDef;
    ballToArmJointDef.Initialize(pBumper->GetBody(), pBumperArm->GetBody(), ballToArmJoint);
    m_pWorld->CreateJoint(&ballToArmJointDef);

    b2RevoluteJointDef armJointDef; //this is the movement and anchor point of the bumpers arm
    b2Vec2 anchorPosArm(0, 1);
    armJointDef.Initialize(pGround, pBumperArm->GetBody(), anchorPosArm);
    armJointDef.enableMotor = true;
    armJointDef.motorSpeed = 10;
    armJointDef.maxMotorTorque = 20;
    m_pWorld->CreateJoint(&armJointDef);
    

    //padles
    fw::GameObject* pPadleLeft = new fw::GameObject(m_pGameCore, "Padle Left", vec3(-5.55f, -7.5, 0), getMesh("RightTriangle"), getMaterial("Yellow"));
    pPadleLeft->SetScale(vec3(10, 2, 1));
    pPadleLeft->CreateBody(m_pWorld, true, Box2dShapes::RightTriangle, PhysicsCategory_Padel, padelGroup, 0, false);
    m_Objects.push_back(pPadleLeft);

    b2Vec2 anchorPosLeftPadle(-10.55f, -8.5); //the left padels movement and anchor
    leftPadleJointDef.Initialize(pGround, pPadleLeft->GetBody(), anchorPosLeftPadle);
    leftPadleJointDef.lowerAngle = 0; 
    leftPadleJointDef.upperAngle = 45 * b2_pi / 180.0f;
    leftPadleJointDef.enableLimit = true;
    leftPadleJointDef.enableMotor = true;
    leftPadleJointDef.motorSpeed = 1000;
    leftPadleJointDef.maxMotorTorque = 1250;
    leftPadleJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&leftPadleJointDef);

    fw::GameObject* pPadleRight = new fw::GameObject(m_pGameCore, "Padle Right", vec3(5.55f, -7.5, 0), getMesh("RightTriangleFliped"), getMaterial("Yellow"));
    pPadleRight->SetScale(vec3(10, 2, 1));
    pPadleRight->CreateBody(m_pWorld, true, Box2dShapes::RightTriangleFliped, PhysicsCategory_Padel, padelGroup, 0, false);
    m_Objects.push_back(pPadleRight);

    b2Vec2 anchorPosRightPadle(10.55f, -8.5); //the right padels movement and anchor
    rightPadleJointDef.Initialize(pGround, pPadleRight->GetBody(), anchorPosRightPadle);
    rightPadleJointDef.enableLimit = true;
    rightPadleJointDef.lowerAngle = -45 * b2_pi / 180.0f;
    rightPadleJointDef.upperAngle = 0;
    rightPadleJointDef.enableMotor = true;
    rightPadleJointDef.motorSpeed = -1000;
    rightPadleJointDef.maxMotorTorque = 1250;
    rightPadleJoint = (b2RevoluteJoint*)m_pWorld->CreateJoint(&rightPadleJointDef);

    m_ContactListener = new PinBallContactListener();

    m_pWorld->SetContactListener(m_ContactListener);
}

PinBallScene::~PinBallScene()
{
    delete m_ContactListener;
}

void PinBallScene::Update(float deltaTime)
{
    m_pWorld->Step(1 / 60.0f, 8, 3);

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    if (greenBarJoint->GetJointTranslation() >= greenBarJointDef.upperTranslation || greenBarJoint->GetJointTranslation() <= greenBarJointDef.lowerTranslation)  //moves the green bar side to side
    {
        greenBarJointDef.motorSpeed = -greenBarJointDef.motorSpeed;
        greenBarJoint->SetMotorSpeed(greenBarJointDef.motorSpeed);
    }

    for (b2Contact* contact = m_pWorld->GetContactList(); contact != nullptr; contact = contact->GetNext()) //this is collsion checks with the floor and balls, i tryed to get it in the concatcte lisnser but it was crashing evrytime
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        if (contact->IsTouching() && contact->GetManifold()->pointCount > 0 && (((fixtureB->GetFilterData().categoryBits & PhysicsCategory_Red) || (fixtureB->GetFilterData().categoryBits & PhysicsCategory_Green) || (fixtureB->GetFilterData().categoryBits & PhysicsCategory_Blue)) && (fixtureA->GetFilterData().categoryBits & PhysicsCategory_Floor))) //if a ball is touching a floor
        {
            for (fw::GameObject* pObject : m_Objects) //loops threought all game objects
            {
                b2Body* objectBody = pObject->GetBody();
                if (objectBody == fixtureB->GetBody()) //if they are the smae body
                {
                    if (objectBody->GetPosition().x <= 0)
                    {
                        pObject->SetPosition(vec3(-11.5f, 2, 0));
                    }
                    else
                    {
                        pObject->SetPosition(vec3(11.5f, 2, 0));
                    }
                    objectBody->SetLinearVelocity(b2Vec2(0, 0));
                    objectBody->SetAngularVelocity(0);
                    break;
                }
            }
        }
    }

    if (m_pVirtualController != nullptr)
    {
        if (m_pVirtualController->IsActionHeld(VirtualController::Actions::Jump)) //when held the padles go up
        {
            leftPadleJointDef.motorSpeed = 1000;
            rightPadleJointDef.motorSpeed = -1000;

            rightPadleJoint->SetMotorSpeed(rightPadleJointDef.motorSpeed);
            leftPadleJoint->SetMotorSpeed(leftPadleJointDef.motorSpeed);
        }
        else //sets them to go back down
        {
            leftPadleJointDef.motorSpeed = -1000;
            rightPadleJointDef.motorSpeed = 1000;

            rightPadleJoint->SetMotorSpeed(rightPadleJointDef.motorSpeed);
            leftPadleJoint->SetMotorSpeed(leftPadleJointDef.motorSpeed);
        }
    }

    m_pCamera->Update(deltaTime);

}

void PinBallScene::Draw()
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

void PinBallScene::OnEvent(fw::Event* pEvent)
{

}

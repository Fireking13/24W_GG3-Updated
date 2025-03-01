//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "ScenesSystem/Scene.h"
#include "Events/GameEvents.h"
#include "Game.h"


enum PhysicsCategoriesMoonLanding
{
    PhysicsCategoriesMoonLanding_Player = 1 << 0,
    PhysicsCategoriesMoonLanding_Ground = 1 << 1,
    PhysicsCategoriesMoonLanding_Fire = 1 << 2,
    PhysicsCategoriesMoonLanding_Leg = 1 << 3,
    PhysicsCategoriesMoonLanding_LandingPad = 1 << 4,
    PhysicsCategoriesMoonLanding_None = 1 << 5,
};


class MoonLandingContactListener : public b2ContactListener
{
public:
    MoonLandingContactListener(Game* pGame)
    {
        m_Game = pGame;
    }

    virtual void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtureB = contact->GetFixtureB();
        b2Fixture* fixtureA = contact->GetFixtureA();

        fw::Event* pEvent = new ColisionGameEvent(fixtureA, fixtureB);
        m_Game->GetEventManager()->addEvent(pEvent);
        // Send pEven to eventManager;


    }

private:
    Game* m_Game;
};



class MoonLandingScene : public fw::Scene
{
public:
    MoonLandingScene(Game* pGame);
    virtual ~MoonLandingScene();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void OnEvent(fw::Event* pEvent) override;

    bool IsLeg(b2Fixture* fixture);
    bool IsPad(b2Fixture* fixture);
    bool IsGround(b2Fixture* fixture);
    bool IsPlayer(b2Fixture* fixture);

protected:
    b2Body* pGround;

    fw::GameObject* pLeftThuster;
    fw::GameObject* pRightThuster;

    fw::GameObject* pLeftFire;
    fw::GameObject* pRightFire;

    fw::GameObject* pLeftLeg;
    fw::GameObject* pRightLeg;

    std::vector<fw::GameObject*> m_LandingPadList;

    b2WeldJointDef leftWeldJointDef, rightWeldJointDef, leftLegWeldJointDef, rightLegWeldJointDef, leftFireWeldJointDef, rightFireWeldJointDef;

    b2Vec2 pivotLeft;
    b2Vec2 pivotRight;
    b2Vec2 pivotLeftLeg;
    b2Vec2 pivotRightLeg;
    b2Vec2 pivotLeftFire;
    b2Vec2 pivotRightFire;

    b2Joint* leftWeldJoint;
    b2Joint* rightWeldJoint;
    b2Joint* leftLegWeldJoint;
    b2Joint* rightLegWeldJoint;
    b2Joint* leftFireWeldJoint;
    b2Joint* rightFireWeldJoint;

    uint16 PlayerGroup;
    uint16 GroundGroup;
    uint16 LandingPadGroup;
    uint16 LegGroup;
    uint16 FireGroup;

    MoonLandingContactListener* m_ContactListener;
    Game* m_Game = nullptr;

    float minZoom;
    float maxZoom;

    bool leftLegOn;
    bool rightLegOn;

    bool hasLanded;
    bool hasCrashed;

    float angularDamping;

    std::string missionSupportText;
};







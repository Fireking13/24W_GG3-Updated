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

class Game;

enum PhysicsCategories
    {
        PhysicsCategory_Wall = 1 << 0,
        PhysicsCategory_Floor = 1 << 1,
        PhysicsCategory_Padel = 1 << 2,
        PhysicsCategory_Red = 1 << 3,
        PhysicsCategory_Green = 1 << 4,
        PhysicsCategory_Blue = 1 << 5,
        PhysicsCategory_Bumper = 1 << 6,
    };


class PinBallContactListener : public b2ContactListener
{
public:
    PinBallContactListener() {}

    virtual void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        if (IsBumper(fixtureA) || IsBumper(fixtureB))
        {
            HandleBumperCollision(fixtureA, fixtureB);
        }
    }

private:
    bool IsBumper(b2Fixture* fixture)
    {
        return fixture->GetFilterData().categoryBits == PhysicsCategory_Bumper;
    }

    bool IsFloor(b2Fixture* fixture)
    {
        return fixture->GetFilterData().categoryBits == PhysicsCategory_Floor;
    }

    void HandleBumperCollision(b2Fixture* fixtureA, b2Fixture* fixtureB) //chouses which one to send to HandleBumperCollisionend to bounce off the bumber and to not send the bumber to be bumbed 
    {
        if ((fixtureA->GetFilterData().categoryBits & PhysicsCategory_Bumper) && !(fixtureB->GetFilterData().categoryBits & PhysicsCategory_Bumper) && fixtureB->GetFilterData().categoryBits == PhysicsCategory_Red || fixtureB->GetFilterData().categoryBits == PhysicsCategory_Green || fixtureB->GetFilterData().categoryBits == PhysicsCategory_Blue)
        {//if fixtureB is ball and fixtureA is a bumber do this
            HandleBumperCollisionEnd(fixtureB);
        }
        else if ((fixtureB->GetFilterData().categoryBits & PhysicsCategory_Bumper) && !(fixtureA->GetFilterData().categoryBits & PhysicsCategory_Bumper) && fixtureA->GetFilterData().categoryBits == PhysicsCategory_Red || fixtureA->GetFilterData().categoryBits == PhysicsCategory_Green || fixtureA->GetFilterData().categoryBits == PhysicsCategory_Blue)
        {//else if fixtureA is ball and fixtureB is a bumber do this. no 2 bumbers so no flat else()
            HandleBumperCollisionEnd(fixtureA);
        }
    }

    void HandleBumperCollisionEnd(b2Fixture* objectFixture)
    {
        b2Body* objectBody = objectFixture->GetBody();
        b2Vec2 velocity = objectBody->GetLinearVelocity();
        float impulseMagnitude = 5.0f;
        b2Vec2 impulse = -velocity;
        impulse.Normalize();
        impulse *= impulseMagnitude;

        objectBody->ApplyLinearImpulse(impulse, objectBody->GetWorldCenter(), true);
    }
};



class PinBallScene : public fw::Scene
{
public:
    PinBallScene(Game* pGame);
    virtual ~PinBallScene();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void OnEvent(fw::Event* pEvent) override;

protected:
    b2PrismaticJointDef greenBarJointDef;
    b2PrismaticJoint* greenBarJoint;

    b2RevoluteJointDef rightPadleJointDef;
    b2RevoluteJoint* rightPadleJoint;

    b2RevoluteJointDef leftPadleJointDef;
    b2RevoluteJoint* leftPadleJoint;

    PinBallContactListener* m_ContactListener;
};





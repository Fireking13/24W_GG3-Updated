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



extern bool leftwallHit;
extern bool rightwallHit;

class Game;


enum PhysicsCategoriesMidterm
    {
        PhysicsCategoriesMidterm_WallLeft = 1 << 0,
        PhysicsCategoriesMidterm_WallRight = 1 << 1,
        PhysicsCategoriesMidterm_Player = 1 << 2,
        PhysicsCategoriesMidterm_Box = 1 << 3,
    };


class MidtermSceneContactListener : public b2ContactListener
{
public:
    MidtermSceneContactListener() {}

    virtual void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        if (IsLeftWall(fixtureA) || IsLeftWall(fixtureB))
        {
            HandleLeftWallCollision(fixtureA, fixtureB);
        }

        if (IsRightWall(fixtureA) || IsRightWall(fixtureB))
        {
            HandleRightWallCollision(fixtureA, fixtureB);
        }
    }

private:
    bool IsLeftWall(b2Fixture* fixture)
    {
        return fixture->GetFilterData().categoryBits == PhysicsCategoriesMidterm_WallLeft;
    }
    bool IsRightWall(b2Fixture* fixture)
    {
        return fixture->GetFilterData().categoryBits == PhysicsCategoriesMidterm_WallRight;
    }

    bool IsPlayer(b2Fixture* fixture)
    {
        return fixture->GetFilterData().categoryBits == PhysicsCategoriesMidterm_Player;
    }

    void HandleLeftWallCollision(b2Fixture* fixtureA, b2Fixture* fixtureB) 
    {
        leftwallHit = true;
    }

    void HandleRightWallCollision(b2Fixture* fixtureA, b2Fixture* fixtureB)
    {
        rightwallHit = true;
    }

};



class MidtermScene : public fw::Scene
{
public:
    MidtermScene(Game* pGame);
    virtual ~MidtermScene();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void OnEvent(fw::Event* pEvent) override;

    b2Joint* jointLeft = nullptr;
    b2Joint* jointRight = nullptr;
protected:
    b2RevoluteJointDef jointDefLeft;
    b2RevoluteJointDef jointDefRight;

    fw::GameObject* pObject2;
    fw::GameObject* pObject1;

    MidtermSceneContactListener* m_ContactListener;
};





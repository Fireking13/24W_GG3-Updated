//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

class RemoveFromGameEvent : public fw::Event
{
public:
    RemoveFromGameEvent(fw::GameObject* pObject)
    {
        m_pObject = pObject;
    }
    virtual ~RemoveFromGameEvent() {}

    static const char* GetStaticEventType() { return "RemoveFromGameEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    fw::GameObject* GetGameObject() { return m_pObject; }

protected:
    fw::GameObject* m_pObject;
};

class ColisionGameEvent : public fw::Event
{
public:
    ColisionGameEvent(b2Fixture* FixtureA, b2Fixture* FixtureB)
    {
        m_FixtureA = FixtureA;
        m_FixtureB = FixtureB;
    }
    virtual ~ColisionGameEvent() {}

    static const char* GetStaticEventType() { return "ColisionGameEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    b2Fixture* GetFixtureA() { return m_FixtureA; }
    b2Fixture* GetFixtureB() { return m_FixtureB; }

protected:
    b2Fixture* m_FixtureA;
    b2Fixture* m_FixtureB;
};
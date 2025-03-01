//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "Camera.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"


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

namespace fw {

    GameObject::GameObject(GameCore* pGameCore, std::string name, vec3 pos, Mesh* pMesh, Material* pMaterial)
        : m_pGameCore(pGameCore)
        , m_Name(name)
        , m_Position(pos)
        , m_pMesh(pMesh)
        , m_pMaterial(pMaterial)
    {
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Update(float deltaTime)
    {
        //syinc the body to mesh
        if (m_Body)
        {
            m_Position = vec3(m_Body->GetPosition().x, m_Body->GetPosition().y, m_Position.z);
            m_Rotation.z = -radsToDegrees(m_Body->GetAngle());
        }
        if (m_JoltBody)
        {
            m_Position = vec3(m_JoltBody->GetPosition().GetX(), m_JoltBody->GetPosition().GetY(), m_JoltBody->GetPosition().GetZ());
            m_Rotation = vec3(m_JoltBody->GetRotation().GetX(), m_JoltBody->GetRotation().GetY(), m_JoltBody->GetRotation().GetZ());
        }
    }

    void GameObject::Draw(Camera* pCamera)
    {
        Uniforms* pUniforms = m_pGameCore->GetUniforms();

        mat4 transform;
        transform.CreateSRT(m_Scale, m_Rotation, m_Position);
        bgfx::setUniform(pUniforms->GetUniform("u_MatWorld"), &transform);

        mat4 rotationMatrix;
        rotationMatrix.CreateRotation(m_Rotation);
        bgfx::setUniform(pUniforms->GetUniform("u_MatWorldRotation"), &rotationMatrix);

        m_pMesh->Draw(0, pUniforms, m_pMaterial);
    }

    void GameObject::SetPosition(vec3 pos)
    {
        m_Position = pos;
        if (m_Body)
        {
            b2Vec2 newPos(m_Position.x, m_Position.y);
            m_Body->SetTransform(newPos, m_Body->GetAngle());
        }

        if (m_JoltBody)
        {
            JPH::RVec3 newPos(m_Position.x, m_Position.y, m_Position.z);
            m_JoltBody->GetBodyCreationSettings().mPosition = newPos;
        }
    }

    void GameObject::SetRotation(vec3 rot)
    {
        m_Rotation = rot;
        if (m_Body)
        {
            float newAngle = -degreesToRads(m_Rotation.z);
            m_Body->SetTransform(m_Body->GetPosition(), newAngle);
        }
        if (m_JoltBody)
        {
            JPH::Mat44 rotMat = JPH::Mat44::sRotationY(-rot.y / 180 * PI) * JPH::Mat44::sRotationX(-rot.x / 180 * PI) * JPH::Mat44::sRotationZ(-rot.z / 180 * PI);
            JPH::Quat quat = rotMat.GetQuaternion();
            m_JoltBody->GetBodyCreationSettings().mRotation = quat;
        }
    }

    void GameObject::CreateBody(b2World* world, bool gravity, Box2dShapes shapeName, uint16 colType, uint16 groupCol, float restitution, bool sencor)
    {
        //change baced on mesh shape

        b2BodyDef bodyDef;
        bodyDef.userData.pointer = (uintptr_t)this;

        bodyDef.position = b2Vec2(m_Position.x, m_Position.y);
        bodyDef.angle = -degreesToRads(m_Rotation.z);

        if (gravity)
        {
            bodyDef.type = b2_dynamicBody;
        }
        else
        {
            bodyDef.type = b2_staticBody;
        }

        if (shapeName == Box2dShapes::Circle)
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2CircleShape circleShape;
            circleShape.m_radius = m_Scale.x / 2;
            fixtureDef.shape = &circleShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
        else if (shapeName == Box2dShapes::Square)
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(m_Scale.x / 2, m_Scale.y / 2);
            fixtureDef.shape = &polygonShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
        else if (shapeName == Box2dShapes::Triangle)
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2Vec2 vertices[3] = {
            b2Vec2(0.0f, m_Scale.y / 2.0f),                     //top
            b2Vec2(-(m_Scale.x / 2.0f), -(m_Scale.y / 2.0f)),   //bottom left
            b2Vec2(m_Scale.x / 2.0f, -(m_Scale.y / 2.0f)),      //bottom right
            };
            b2PolygonShape polygonShape;
            polygonShape.Set(vertices, 3);
            fixtureDef.shape = &polygonShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
        else if (shapeName == Box2dShapes::RightTriangle)
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2Vec2 vertices[3] = {
            b2Vec2(-(m_Scale.x / 2.0f), m_Scale.y / 2.0f),      //top
            b2Vec2(-(m_Scale.x / 2.0f), -(m_Scale.y / 2.0f)),   //bottom left
            b2Vec2(m_Scale.x / 2.0f, -(m_Scale.y / 2.0f)),      //bottom right
            };
            b2PolygonShape polygonShape;
            polygonShape.Set(vertices, 3);
            fixtureDef.shape = &polygonShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
        else if (shapeName == Box2dShapes::RightTriangleFliped)
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2Vec2 vertices[3] = {
            b2Vec2(m_Scale.x / 2.0f, m_Scale.y / 2.0f),         //top
            b2Vec2(-(m_Scale.x / 2.0f), -(m_Scale.y / 2.0f)),   //bottom left
            b2Vec2(m_Scale.x / 2.0f, -(m_Scale.y / 2.0f)),      //bottom right
            };
            b2PolygonShape polygonShape;
            polygonShape.Set(vertices, 3);
            fixtureDef.shape = &polygonShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
        else if (shapeName == Box2dShapes::Octagon)
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2Vec2 vertices[8] = {
            b2Vec2(-0.5f * m_Scale.x, -0.8536f * m_Scale.y),    // bottom left
            b2Vec2(-0.3536f * m_Scale.x, -1.3536f * m_Scale.y), // left mid bottom
            b2Vec2(0.3536f * m_Scale.x, -1.3536f * m_Scale.y),  // bottom right
            b2Vec2(0.5f * m_Scale.x, -0.8536f * m_Scale.y),     // right mid bottom
            b2Vec2(0.5f * m_Scale.x, 0.8536f * m_Scale.y),      // right mid top
            b2Vec2(0.3536f * m_Scale.x, 1.3536f * m_Scale.y),   // top right
            b2Vec2(-0.3536f * m_Scale.x, 1.3536f * m_Scale.y),  // top left
            b2Vec2(-0.5f * m_Scale.x, 0.8536f * m_Scale.y),     // left mid top
            };
            b2PolygonShape polygonShape;
            polygonShape.Set(vertices, 8);
            fixtureDef.shape = &polygonShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
        else //place holder defult curently a Square
        {
            m_Body = world->CreateBody(&bodyDef);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(m_Scale.x / 2, m_Scale.y / 2);
            fixtureDef.shape = &polygonShape;
            fixtureDef.restitution = restitution;
            fixtureDef.filter.categoryBits = colType;
            fixtureDef.filter.maskBits = groupCol;
            fixtureDef.isSensor = sencor;
            m_Body->CreateFixture(&fixtureDef);
        }
    }

    void GameObject::RemoveBody()
    {
        m_Body = nullptr;
    }

    void GameObject::RemoveJoltBody()
    {
        m_JoltBody = nullptr;
    }



} // namespace fw

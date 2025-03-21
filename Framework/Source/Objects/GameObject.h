//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Math/Vector.h"

#define B2_USER_SETTINGS //rember this always
#include "../Libraries/box2d/include/box2d/box2d.h"

enum Box2dShapes
{
    Circle,
    Square,
    Triangle,
    RightTriangle,
    RightTriangleFliped,
    Octagon
};

namespace JPH 
{
    class Body;
}

namespace fw {

    class Camera;
    class GameCore;
    class Material;
    class Mesh;
    class Uniforms;
    

    class GameObject
    {
    public:
        GameObject(GameCore* pGameCore, std::string name, vec3 pos, Mesh* pMesh, Material* pMaterial);
        virtual ~GameObject();

        virtual void Update(float deltaTime);
        virtual void Draw(Camera* pCamera);

        // Getters.
        std::string GetName() { return m_Name; }

        Mesh* GetMesh() { return m_pMesh; }
        Material* GetMaterial() { return m_pMaterial; }

        vec3 GetPosition() { return m_Position; }
        vec3 GetRotation() { return m_Rotation; }
        vec3 GetScale() { return m_Scale; }
        b2Body* GetBody() { return m_Body; }
        JPH::Body* GetJoltBody() { return m_JoltBody; }
 
        // Setters.
        void SetPosition(vec3 pos);
        void SetRotation(vec3 rot);
        void SetScale(vec3 scale) { m_Scale = scale; }
        void SetMesh(Mesh* mesh) { m_pMesh = mesh; }
        void SetMaterial(Material* mat) { m_pMaterial = mat; }

        void SetJoltBody(JPH::Body* body) { m_JoltBody = body; }

        void CreateBody(b2World* world, bool gravity, Box2dShapes shapeName, uint16 colType, uint16 groupCol, float restitution, bool sencor);
        void RemoveBody();
        void RemoveJoltBody();
    protected:
        GameCore* m_pGameCore = nullptr;

        std::string m_Name;

        Mesh* m_pMesh = nullptr;
        Material* m_pMaterial = nullptr;

        vec3 m_Position = vec3(0, 0, 0);
        vec3 m_Rotation = vec3(0, 0, 0);
        vec3 m_Scale = vec3(1, 1, 1);
        b2Body* m_Body = nullptr;

        JPH::Body* m_JoltBody = nullptr;
    };

} // namespace fw

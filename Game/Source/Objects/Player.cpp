//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "Game.h"
#include "GameCore.h"
#include "Objects/Player.h"
#include "Objects\VirtualController.h" 


Player::Player(Game* pGame, std::string name, vec3 pos, fw::Mesh* pMesh, fw::Material* pMaterial)
    : fw::GameObject( pGame, name, pos, pMesh, pMaterial)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    GameObject::Update(deltaTime);
    
    if (m_pVirtualController != nullptr)
    {
        if (m_pVirtualController->IsActionPressed(VirtualController::Actions::Teleport))
        {
            m_Position.x = fw::Random::Float(0, 10);
            m_Position.y = fw::Random::Float(0, 10);
        }
    }

    
}

void Player::SetControler(VirtualController* virtualController)
{
    m_pVirtualController = virtualController;
}

vec3 Player::GetForwardVector()
{
    //float yaw = degreesToRadians(m_Rotation.y); 
    //float pitch = degreesToRadians(m_Rotation.x); 

    //float x = cos(yaw) * cos(pitch);
    //float y = sin(pitch);
    //float z = sin(yaw) * cos(pitch);

    //return vec3(x, y, z).Normalize();

    float yaw = degreesToRadians(m_Rotation.y-90);

    float x = cos(yaw);
    float z = sin(yaw);

    return vec3(x, 0, z);

}

vec3 Player::GetRightVector()
{
    //vec3 forward = GetForwardVector();
    //vec3 up = vec3(0, 1, 0);
    //return forward.Cross(up).Normalize();

    float yaw = degreesToRadians(m_Rotation.y-180.0f);

    float x = cos(yaw);
    float z = sin(yaw);

    return vec3(x, 0, z);
}

float Player::degreesToRadians(float degrees)
{
    return degrees * 3.14159265359f / 180.0f;
}

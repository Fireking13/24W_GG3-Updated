//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "ThridPersonCamera.h"
#include "FWCore.h"
#include "GameCore.h"
#include "Utility/Uniforms.h"
#include <algorithm>

namespace fw {

    ThridPersonCamera::ThridPersonCamera(GameCore* pGameCore, vec3 pos, vec3 eye, vec3 up, vec3 at, float Disctince, GameObject* target)
        : Camera( pGameCore, pos, eye, up, at)
    {
        m_Distince = Disctince;
        m_Target = target;
        m_GameCore = pGameCore;
    }

    ThridPersonCamera::~ThridPersonCamera()
    {
    }

    void ThridPersonCamera::Update(float32 deltaTime)
    {
        vec2 rotationSpeed = vec2(1.0f, 0.4f);

        if (m_GameCore->GetFramework()->IsKeyDown('J'))
            m_Rotation.y += 90 * deltaTime * rotationSpeed.x;
        if (m_GameCore->GetFramework()->IsKeyDown('L'))
            m_Rotation.y -= 90 * deltaTime * rotationSpeed.x;
        if (m_GameCore->GetFramework()->IsKeyDown('I'))
            m_Rotation.x -= 90 * deltaTime * rotationSpeed.y;
        if (m_GameCore->GetFramework()->IsKeyDown('K'))
            m_Rotation.x += 90 * deltaTime * rotationSpeed.y;

        if (m_GameCore->GetFramework()->IsKeyDown('U'))
            m_Distince -= 10 * deltaTime;
        if (m_GameCore->GetFramework()->IsKeyDown('M'))
            m_Distince += 10 * deltaTime;

        m_Distince = std::clamp(m_Distince, 0.1f, 100.0f);
        m_Rotation.x = std::clamp(m_Rotation.x, -89.9f, 89.9f);

        // Calculate eye offset.
        // Method 1.
        float sx = sin(m_Rotation.x / 180 * PI);
        float sy = sin(m_Rotation.y / 180 * PI);
        float cx = cos(m_Rotation.x / 180 * PI);
        float cy = cos(m_Rotation.y / 180 * PI);
        vec3 offset = vec3(cx * sy * m_Distince, -sx * m_Distince, -1 * cx * cy * m_Distince);

        m_Eye = m_Target->GetPosition() + offset;
        m_At = m_Target->GetPosition();
        m_Up = vec3(0, 1, 0);
    }

} // namespace fw

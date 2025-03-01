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
#include "FWCore.h"
#include "GameCore.h"
#include "Utility/Uniforms.h"

namespace fw {

    Camera::Camera(GameCore* pGameCore, vec3 pos, vec3 eye, vec3 up, vec3 at)
        : GameObject( pGameCore, "Camera", pos, nullptr, nullptr)
    {
        m_Eye = eye;
        m_Up = up;
        m_At = at;

        FWCore* pFW = pGameCore->GetFramework();
        SetAspectRatio( (float)pFW->GetWindowClientWidth()/pFW->GetWindowClientHeight() );
    }

    Camera::~Camera()
    {
    }

    void Camera::Update(float32 deltaTime)
    {

    }

    void Camera::Enable(int viewID)
    {
        Uniforms* pUniforms = m_pGameCore->GetUniforms();
        vec2 scaleWithAspectRatio = m_ProjectionScale * vec2( 1.0f/m_AspectRatio, 1 );

        mat4 viewMatrix;
        viewMatrix.CreateLookAtView(m_Position + m_Eye, m_Up, m_Position + m_At); 
        bgfx::setUniform(pUniforms->GetUniform("u_MatView"), &viewMatrix);

        mat4 projMatrix;
        projMatrix.CreatePerspectiveVFoV(45, m_AspectRatio, 0.01f, 100.0f);
        bgfx::setUniform(pUniforms->GetUniform("u_MatProj"), &projMatrix);
    }

    vec3 Camera::GetForwardVector()
    {
        float sx = sin(m_Rotation.x / 180 * PI);
        float sy = sin(m_Rotation.y / 180 * PI);
        float cx = cos(m_Rotation.x / 180 * PI);
        float cy = cos(m_Rotation.y / 180 * PI);

        vec3 forward = vec3(cx * cy, -sx, -cx * sy);

        return forward;
    }

} // namespace fw

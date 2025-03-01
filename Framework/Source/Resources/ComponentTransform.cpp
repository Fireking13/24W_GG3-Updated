//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "ComponentTransform.h"


namespace fw {

    ComponentTransform::ComponentTransform(GameObject* gameObject, vec3 scale, vec3 rotation, vec3 position, mat4 transform)
        : Component(gameObject)
    {
        m_Scale = scale;
        m_Rotation = rotation;
        m_Position = position;
        m_Transform = transform;
    }

    ComponentTransform::~ComponentTransform()
    {
    }

} // namespace fw

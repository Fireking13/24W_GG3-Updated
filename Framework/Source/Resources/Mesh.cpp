//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "bgfx/platform.h"

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Math/Matrix.h"
#include "Resources/Material.h"
#include "Utility/Utility.h"

namespace fw {

    Mesh::Mesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize)
    {
        Create( vertexFormat, verts, vertsSize, indices, indicesSize );
    }

    Mesh::~Mesh()
    {
        bgfx::destroy( m_VBO );
        bgfx::destroy( m_IBO );
    }

    void Mesh::Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize)
    {
        m_VBO = bgfx::createVertexBuffer( bgfx::copy(verts, vertsSize), vertexFormat );
        m_IBO = bgfx::createIndexBuffer( bgfx::copy(indices, indicesSize) );
    }

    void Mesh::Draw(bgfx::ViewId viewID, const Uniforms* pUniforms, const Material* pMaterial)
    {
        // Set vertex and index buffer.
        bgfx::setVertexBuffer( 0, m_VBO );
        bgfx::setIndexBuffer( m_IBO );

        // Setup the material's uniforms.
        pMaterial->Enable( pUniforms );

        // Set render states.
        uint64_t state = pMaterial->GetBGFXRenderState() | BGFX_STATE_MSAA;
        bgfx::setState( state );

        // Submit primitive for rendering to the selected view.
        bgfx::submit( viewID, pMaterial->GetShader()->GetProgram() );
    }


    void Mesh::setPos(std::vector<vec3> positions)
    {
        VertsPos = positions;
    }

    vec3 Mesh::getPos(int x, int z)
    {
        if (x > -1 && z > -1 && x <= vertsSizeX && z <= vertsSizeZ)
        {
            int index = z * vertsSizeX + x;
            if (VertsPos.size() > 0 && VertsPos.size() - 1 >= index)
            {
                return VertsPos[index];
            }
        }
        return vec3();
    }

    void Mesh::setX(int x)
    {
        vertsSizeX = x;
    }

    void Mesh::setZ(int y)
    {
        vertsSizeZ = y;
    }

    void Mesh::setSize(vec2 size)
    {
        m_Size = size;
    }

    float Mesh::GetHeightAtXZ(float x, float z)
    {
        float height = 0;

        if (x < 0 || x >= m_Size.x || z < 0 || z >= m_Size.y) {
            // Return default height if out of range
            return height;
        }

        // Convert x,z to heightmap indices.
        float xPercent = x / m_Size.x;
        float zPercent = z / m_Size.y;
        int xIndex = (int)(xPercent * (vertsSizeX - 1));
        int zIndex = (int)(zPercent * (vertsSizeZ - 1));

        // Get the 4 vertices that make up the quad.
        int stride = vertsSizeX;
        int index = zIndex * stride + xIndex;
        vec3 bottomLeft = VertsPos[index];
        vec3 bottomRight = VertsPos[index + 1];
        vec3 topLeft = VertsPos[index + stride];
        vec3 topRight = VertsPos[index + stride + 1];

        // Get the x,z percent within the quad.
        float xPercentInQuad = xPercent * (vertsSizeX - 1) - xIndex;
        float zPercentInQuad = zPercent * (vertsSizeZ - 1) - zIndex;

        // Get the height at x,z.
        vec3 p1, p2, p3;
        if (xPercentInQuad < zPercentInQuad)
        {
            // Top left triangle.
            p1 = vec3(0, topLeft.y, 1);
            p2 = vec3(1, topRight.y, 1);
            p3 = vec3(0, bottomLeft.y, 0);
        }
        else
        {
            // Bottom right triangle.
            p1 = vec3(1, topRight.y, 1);
            p2 = vec3(1, bottomRight.y, 0);
            p3 = vec3(0, bottomLeft.y, 0);
        }

        // Barycentric interpolation.
        {
            vec2 p0 = vec2(xPercentInQuad, zPercentInQuad);

            // Calculate Vectors.
            vec2 p10 = p0 - p1.XZ();
            vec2 p12 = p2.XZ() - p1.XZ();
            vec2 p13 = p3.XZ() - p1.XZ();

            // Cross products.
            float a123 = (p12.x * p13.y - p12.y * p13.x);
            float a3 = (p12.x * p10.y - p12.y * p10.x);
            float a2 = (p10.x * p13.y - p10.y * p13.x);

            // Weights.
            float w3 = a3 / a123;
            float w2 = a2 / a123;
            float w1 = 1.0f - w2 - w3;

            // Apply weights.
            height = (w1 * p1.y) + (w2 * p2.y) + (w3 * p3.y);
        }

        return height;
    }
} // namespace fw

//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"


#include "stb/stb_image.h"

#include "VertexFormats.h"
#include "Shapes.h"

//=======================
// Triangle
//=======================
static const VertexFormat_PosColor g_TriangleVerts[] =
{
    { vec2( 0.0f, 0.5f), 255, 0, 0, 255 }, // Top
    { vec2(-0.5f,-0.5f), 0, 255, 0, 255 }, // Bottom-left
    { vec2( 0.5f,-0.5f), 0, 0, 255, 255 }, // Bottom-right
};
static const uint16 g_TriangleIndices[] =
{
    0, 2, 1,
};
fw::Mesh* CreateTriangleMesh()
{
    return new fw::Mesh( VertexFormat_PosColor::format, g_TriangleVerts, sizeof(g_TriangleVerts), g_TriangleIndices, sizeof(g_TriangleIndices) );
}

//=======================
// Square
//=======================
static const VertexFormat_PosColor g_SquareVerts[] =
{
    { vec2(-0.5f, 0.5f), 0, 255, 0, 255 }, // Top-left
    { vec2(-0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-left
    { vec2( 0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-right
    { vec2( 0.5f, 0.5f), 0, 255, 0, 255 }, // Top-right
};
static const uint16 g_SquareIndices[] =
{
    0,2,1, 0,3,2
};
fw::Mesh* CreateSquareMesh()
{
    return new fw::Mesh( VertexFormat_PosColor::format, g_SquareVerts, sizeof(g_SquareVerts), g_SquareIndices, sizeof(g_SquareIndices) );
}

fw::Mesh* CreateCircleMesh()
{
    int numPoints = 32;

    std::vector<VertexFormat_PosColor> verts;
    std::vector<uint16> indices;

    float angleInc = 2 * PI / numPoints;
    float radius = 0.5f;

    for (int i = 0; i < numPoints; i++)
    {
        float angle = angleInc * i;
        vec2 pos = vec2(cos(angle), sin(angle)) * radius;
        verts.push_back({ pos, 0, 255, 0, 255 });
    }

    for (int i = 1; i < numPoints - 1; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    int vertBytes = sizeof(VertexFormat_PosColor) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh(VertexFormat_PosColor::format, verts.data(), vertBytes, indices.data(), indicesBytes);
}

//=======================
// Sprite
//=======================
static const VertexFormat_PosUV g_SpriteVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0,1) },   // Top-left
    { vec2(-0.5f,-0.5f), vec2(0,0) },   // Bottom-left
    { vec2( 0.5f,-0.5f), vec2(1,0) },   // Bottom-right
    { vec2( 0.5f, 0.5f), vec2(1,1) },   // Top-right
};
static const uint16 g_SpriteIndices[] =
{
    0,2,1, 0,3,2
};
fw::Mesh* CreateSpriteMesh()
{
    return new fw::Mesh( VertexFormat_PosUV::format, g_SpriteVerts, sizeof(g_SpriteVerts), g_SpriteIndices, sizeof(g_SpriteIndices) );
}

//=======================
// Right Triangle
//=======================
static const VertexFormat_PosColor g_RightTriangleVerts[] =
{
    { vec2(-0.5f, 0.5f), 255, 0, 0, 255 },  // Top
    { vec2(-0.5f,-0.5f), 0, 255, 0, 255 },  // Bottom-left
    { vec2(0.5f,-0.5f), 0, 0, 255, 255 },   // Bottom-right
};

fw::Mesh* CreateRightTriangleMesh()
{
    return new fw::Mesh(VertexFormat_PosColor::format, g_RightTriangleVerts, sizeof(g_RightTriangleVerts), g_TriangleIndices, sizeof(g_TriangleIndices));
}

//=======================
// Right Triangle Fliped
//=======================
static const VertexFormat_PosColor g_RightTriangleVertsFliped[] =
{
    { vec2(0.5f, 0.5f), 255, 0, 0, 255 },  // Top
    { vec2(-0.5f,-0.5f), 0, 255, 0, 255 },  // Bottom-left
    { vec2(0.5f,-0.5f), 0, 0, 255, 255 },   // Bottom-right
};


fw::Mesh* CreateRightTriangleMeshFliped()
{
    return new fw::Mesh(VertexFormat_PosColor::format, g_RightTriangleVertsFliped, sizeof(g_RightTriangleVertsFliped), g_TriangleIndices, sizeof(g_TriangleIndices));
}

//=======================
// Cube
//=======================
static const VertexFormat_PosColor_3D g_CubeVerts[] =
{
    //front
    { vec3(-0.5f, 0.5f, -0.5f), 0, 255, 0, 255 },   //top left
    { vec3(-0.5f,-0.5f, -0.5f), 0, 0, 0, 255 },     //bottom left
    { vec3(0.5f,-0.5f, -0.5f), 0, 0, 0, 255 },      //bottom right
    { vec3(0.5f, 0.5f, -0.5f), 0, 255, 0, 255 },    //top right

    //back
    { vec3(-0.5f, 0.5f, 0.5f), 0, 255, 0, 255 },    //top left
    { vec3(-0.5f,-0.5f, 0.5f), 0, 0, 0, 255 },      //bottom left
    { vec3(0.5f,-0.5f, 0.5f), 0, 0, 0, 255 },       //bottom right
    { vec3(0.5f, 0.5f, 0.5f), 0, 255, 0, 255 },     //top right

    //top
    { vec3(-0.5f, 0.5f, -0.5f), 0, 255, 0, 255 },   //top left
    { vec3(-0.5f, 0.5f, 0.5f), 0, 0, 0, 255 },      //bottom left
    { vec3(0.5f, 0.5f, 0.5f), 0, 0, 0, 255 },       //bottom right
    { vec3(0.5f, 0.5f, -0.5f), 0, 255, 0, 255 },    //top right

    //bottom
    { vec3(-0.5f, -0.5f, -0.5f), 0, 255, 0, 255 },  //top left
    { vec3(-0.5f,-0.5f, 0.5f), 0, 0, 0, 255 },      //bottom left
    { vec3(0.5f,-0.5f, 0.5f), 0, 0, 0, 255 },       //bottom right
    { vec3(0.5f, -0.5f, -0.5f), 0, 255, 0, 255 },   //top right

    //left
    { vec3(-0.5f, 0.5f, 0.5f), 0, 255, 0, 255 },    //top left
    { vec3(-0.5f,-0.5f, 0.5f), 0, 0, 0, 255 },      //bottom left
    { vec3(-0.5f,-0.5f, -0.5f), 0, 0, 0, 255 },     //bottom right
    { vec3(-0.5f, 0.5f, -0.5f), 0, 255, 0, 255 },   //top right

    //right
    { vec3(0.5f, 0.5f, 0.5f), 0, 255, 0, 255 },     //top left
    { vec3(0.5f,-0.5f, 0.5f), 0, 0, 0, 255 },       //bottom left
    { vec3(0.5f,-0.5f, -0.5f), 0, 0, 0, 255 },      //bottom right
    { vec3(0.5f, 0.5f, -0.5f), 0, 255, 0, 255 },    //top right
    
}; 

//=======================
// Dice
//=======================
static const VertexFormat_PosUV_3D g_DiceVerts[] =
{
    //front num 6
    { vec3(-0.5f, 0.5f, -0.5f), vec2(0.33f, 0.25f)}, //top left
    { vec3(-0.5f,-0.5f, -0.5f), vec2(0.33f, 0)},     //bottom left
    { vec3(0.5f,-0.5f, -0.5f), vec2(0.66f, 0)},      //bottom right
    { vec3(0.5f, 0.5f, -0.5f), vec2(0.66f, 0.25f)},  //top right

    //back num 1
    { vec3(-0.5f, 0.5f, 0.5f), vec2(0.33f, 0.75f)},  //top left
    { vec3(-0.5f,-0.5f, 0.5f), vec2(0.33f, 0.5f)},   //bottom left
    { vec3(0.5f,-0.5f, 0.5f), vec2(0.66f, 0.5f)},    //bottom right
    { vec3(0.5f, 0.5f, 0.5f), vec2(0.66f, 0.75f)},   //top right

    //top num 4
    { vec3(-0.5f, 0.5f, -0.5f), vec2(0.33f, 0.5f)},  //top left
    { vec3(-0.5f, 0.5f, 0.5f), vec2(0.33f, 0.25f)},  //bottom left
    { vec3(0.5f, 0.5f, 0.5f), vec2(0.66f, 0.25f)},   //bottom right
    { vec3(0.5f, 0.5f, -0.5f), vec2(0.66f, 0.5f)},   //top right

    //bottom num 3
    { vec3(-0.5f, -0.5f, -0.5f), vec2(0.33f, 1)},    //top left
    { vec3(-0.5f,-0.5f, 0.5f), vec2(0.33f, 0.75f)},  //bottom left
    { vec3(0.5f,-0.5f, 0.5f), vec2(0.66f, 0.75f)},   //bottom right
    { vec3(0.5f, -0.5f, -0.5f), vec2(0.66f, 1)},     //top right

    //left num 5
    { vec3(-0.5f, 0.5f, 0.5f), vec2(0, 0.75f)},      //top left
    { vec3(-0.5f,-0.5f, 0.5f), vec2(0, 0.5f)},       //bottom left
    { vec3(-0.5f,-0.5f, -0.5f), vec2(0.33f, 0.5f)},  //bottom right
    { vec3(-0.5f, 0.5f, -0.5f), vec2(0.33f, 0.75f)}, //top right

    //right num 2
    { vec3(0.5f, 0.5f, 0.5f), vec2(0.66f, 0.75f)},   //top left
    { vec3(0.5f,-0.5f, 0.5f), vec2(0.66f, 0.5f)},    //bottom left
    { vec3(0.5f,-0.5f, -0.5f), vec2(1, 0.5f)},       //bottom right
    { vec3(0.5f, 0.5f, -0.5f), vec2(1, 0.75f)},      //top right
};

static const uint16 g_CubeIndices[] =
{
    0,2,1, 0,3,2,       //front
    4,5,6, 4,6,7,       //back
    8,9,10, 8,10,11,    //top
    12,14,13, 12,15,14, //bottom
    16,18,17, 16,19,18, //left
    20,21,22, 20,22,23  //right
};

fw::Mesh* CreateCubeMesh()
{
    return new fw::Mesh(VertexFormat_PosColor_3D::format, g_CubeVerts, sizeof(g_CubeVerts), g_CubeIndices, sizeof(g_CubeIndices));
}

//=======================
// Ship Hull
//=======================
static const VertexFormat_PosUV g_ShipHullVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0.25f,1) },       // Top-left
    { vec2(-0.5f,-0.5f), vec2(0.25f, 0.25f) },  // Bottom-left
    { vec2(0.5f,-0.5f), vec2(0.75f, 0.25f) },   // Bottom-right
    { vec2(0.5f, 0.5f), vec2(0.75f,1) },        // Top-right
};

//=======================
// Ship thruster
//=======================
static const VertexFormat_PosUV g_ShipThrusterVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0, 0.75f) },      // Top-left
    { vec2(-0.5f,-0.5f), vec2(0, 0.25f) },      // Bottom-left
    { vec2(0.5f,-0.5f), vec2(0.25f, 0.25f) },   // Bottom-right
    { vec2(0.5f, 0.5f), vec2(0.25f, 0.75f) },   // Top-right
};

//=======================
// Ship fire
//=======================
static const VertexFormat_PosUV g_ShipFireVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0,0.25f) },   // Top-left
    { vec2(-0.5f,-0.5f), vec2(0,0) },       // Bottom-left
    { vec2(0.5f,-0.5f), vec2(0.25f,0) },    // Bottom-right
    { vec2(0.5f, 0.5f), vec2(0.25f,0.25f) },// Top-right
};

//=======================
// Ship Leg
//=======================
static const VertexFormat_PosUV g_ShipLegVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0.25f, 0.25f) },          // Top-left
    { vec2(-0.5f,-0.5f), vec2(0.25f, 0) },              // Bottom-left
    { vec2(0.5f,-0.5f), vec2(0.25f + 0.125f, 0) },      // Bottom-right
    { vec2(0.5f, 0.5f), vec2(0.25f + 0.125f, 0.25f) },  // Top-right
};

fw::Mesh* CreateShipHullMesh()
{
    return new fw::Mesh(VertexFormat_PosUV::format, g_ShipHullVerts, sizeof(g_ShipHullVerts), g_SpriteIndices, sizeof(g_SpriteIndices));
}

fw::Mesh* CreateShipThrusterMesh()
{
    return new fw::Mesh(VertexFormat_PosUV::format, g_ShipThrusterVerts, sizeof(g_ShipThrusterVerts), g_SpriteIndices, sizeof(g_SpriteIndices));
}

fw::Mesh* CreateShipFireMesh()
{
    return new fw::Mesh(VertexFormat_PosUV::format, g_ShipFireVerts, sizeof(g_ShipFireVerts), g_SpriteIndices, sizeof(g_SpriteIndices));
}

fw::Mesh* CreateShipLegMesh()
{
    return new fw::Mesh(VertexFormat_PosUV::format, g_ShipLegVerts, sizeof(g_ShipLegVerts), g_SpriteIndices, sizeof(g_SpriteIndices));
}

fw::Mesh* CreateDiceMesh()
{
    return new fw::Mesh(VertexFormat_PosUV_3D::format, g_DiceVerts, sizeof(g_DiceVerts), g_CubeIndices, sizeof(g_CubeIndices));
}

fw::Mesh* CreatePlaneMesh(float xV, float yV, float xW, float yW )
{
    std::vector<VertexFormat_PosUVWave> verts;
    std::vector<uint16> indices;
    
    vec2 vertCount(xV, yV);
    vec2 worldSize(xW, yW);

    float stepX = worldSize.x / (vertCount.x - 1);
    float stepY = worldSize.y / (vertCount.y - 1);

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {
            vec3 pos = vec3(x * stepX, 0, y * stepY); //- (yW / 2) if want centered to 0,0
            vec2 uv = vec2(x * stepX, y * stepY);
            vec3 normal = vec3(0, 1, 0);
            verts.push_back({pos, normal, uv});
        }
    }

    for (int y = 0; y < vertCount.y - 1; y++)
    {
        for (int x = 0; x < vertCount.x - 1; x++)
        {
            float bottomLeftIndex = y * vertCount.x + x;

            indices.push_back(bottomLeftIndex + 0.0f);
            indices.push_back(bottomLeftIndex + vertCount.x);
            indices.push_back(bottomLeftIndex + vertCount.x + 1.0f);

            indices.push_back(bottomLeftIndex + 0.0f);
            indices.push_back(bottomLeftIndex + vertCount.x + 1.0f);
            indices.push_back(bottomLeftIndex + 1.0f);
        }
    }
    

    int vertBytes = sizeof(VertexFormat_PosUVWave) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh(VertexFormat_PosUVWave::format, verts.data(), vertBytes, indices.data(), indicesBytes);
}

fw::Mesh* CreatePlaneHightMesh(float xV, float yV, float xW, float yW, const char* filename)
{
    uint32 length;
    char* fileContents = fw::LoadCompleteFile(filename, &length);
    if (!fileContents)
    {
        return nullptr;
    }

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* pixels = stbi_load_from_memory((unsigned char*)fileContents, length, &width, &height, &channels, 4);
    if (!pixels)
    {
        delete[] fileContents;
        return nullptr;
    }

    float maxHight = 5.0f;

    std::vector<VertexFormat_PosUVWave> verts;
    std::vector<uint16> indices;

    std::vector<vec3> positions;
    std::vector<vec2> uvs;
    std::vector<vec3> normal;

    vec2 vertCount(xV, yV);
    vec2 worldSize(xW, yW);

    float stepX = worldSize.x / (vertCount.x - 1);
    float stepY = worldSize.y / (vertCount.y - 1);

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {
            vec2 uv = vec2(x * stepX, y * stepY); 
            vec2 vertsPos(x * stepX, y * stepY); //- (yW / 2) if want centered to 0,0

            int pixelX = (int)(x * (width - 1) / (vertCount.x - 1));
            int pixelY = (int)(y * (height - 1) / (vertCount.y - 1));

            unsigned char* pixel = &pixels[(pixelY * width + pixelX) * channels];
            float brightness = (pixel[0] + pixel[1] + pixel[2]) / 3.0f / 255.0f;
            float heightValue = pow(brightness, 2) * maxHight;

            vec3 pos = vec3(vertsPos.x, heightValue, vertsPos.y);

            positions.push_back(pos);
            uvs.push_back(uv);
        }
    }

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {

            vec3 up;
            vec3 down;
            vec3 left;
            vec3 right;

            if (y - 1 >= 0)
            {
                down = positions[x + (y - 1) * vertCount.x];
            }
            else
            {
                down = positions[x + y * vertCount.x]; 
            }

            if (y + 1 < vertCount.y)
            {
                up = positions[x + (y + 1) * vertCount.x];
            }
            else
            {
                up = positions[x + y * vertCount.x]; 
            }

            if (x - 1 >= 0)
            {
                left = positions[(x - 1) + y * vertCount.x];
            }
            else
            {
                left = positions[x + y * vertCount.x];
            }

            if (x + 1 < vertCount.x)
            {
                right = positions[(x + 1) + y * vertCount.x];
            }
            else
            {
                right = positions[x + y * vertCount.x]; 
            }

            vec3 upDir = up - down;
            vec3 rightDir = left - right;

            vec3 normal = rightDir.Cross(upDir);

            vec3 pos = positions[x + y * vertCount.x];
            vec2 uv = uvs[x + y * vertCount.x];

            verts.push_back({ pos, normal, uv });
        }
    }

    for (int y = 0; y < vertCount.y - 1; y++)
    {
        for (int x = 0; x < vertCount.x - 1; x++)
        {
            float bottomLeftIndex = y * vertCount.x + x;

            indices.push_back(bottomLeftIndex + 0.0f);
            indices.push_back(bottomLeftIndex + vertCount.x);
            indices.push_back(bottomLeftIndex + vertCount.x + 1.0f);

            indices.push_back(bottomLeftIndex + 0.0f);
            indices.push_back(bottomLeftIndex + vertCount.x + 1.0f);
            indices.push_back(bottomLeftIndex + 1.0f);
        }
    }

    int vertBytes = sizeof(VertexFormat_PosUVWave) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    fw::Mesh* meshNew = new fw::Mesh(VertexFormat_PosUVWave::format, verts.data(), vertBytes, indices.data(), indicesBytes);

    meshNew->setX(xV);
    meshNew->setZ(yV);
    meshNew->setPos(positions);
    meshNew->setSize(worldSize);

    return meshNew;
}


fw::Mesh* CreateObj(const char* fileName)
{
    fw::uint32 length = 0;
    char* buffer = fw::LoadCompleteFile(fileName, &length);
    if (buffer == 0 || length == 0)
    {
        delete[] buffer;
        return nullptr;
    }

    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);

    std::vector<VertexFormat_PosUVWave> verts;
    std::vector<uint16> indices;
    std::vector<vec3> positions;
    std::vector<vec2> uvs;
    std::vector<vec3> normals;

    while (line)
    {
        float x, y, z;

        if (line[0] == 'v')
        {
            if (line[1] == 't')
            {
                sscanf(line, "vt %f %f", &x, &y);
                uvs.push_back(vec2(x, y));
            }
            else if (line[1] == 'n')
            {
                sscanf(line, "vn %f %f %f", &x, &y, &z);
                normals.push_back(vec3(x, y, z));
            }
            else
            {
                sscanf(line, "v %f %f %f", &x, &y, &z);
                positions.push_back(vec3(x, y, z));
            }
        }
        else if (line[0] == 'f')
        {
            int num[9];
            sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                &num[0], &num[1], &num[2],
                &num[3], &num[4], &num[5],
                &num[6], &num[7], &num[8]);

            for (int i = 0; i < 3; ++i)
            {
                verts.push_back({ positions[num[i * 3] - 1], normals[num[i * 3 + 2] - 1], uvs[num[i * 3 + 1] - 1] });
                indices.push_back(verts.size() - 1);
            }
        }

        line = strtok_s(nullptr, "\n", &next_token);
    }

    delete[] buffer;

    int vertBytes = sizeof(VertexFormat_PosUVWave) * static_cast<int>(verts.size());
    int indicesBytes = sizeof(uint16) * static_cast<int>(indices.size());

    return new fw::Mesh(VertexFormat_PosUVWave::format, verts.data(), vertBytes, indices.data(), indicesBytes);
}

fw::Mesh* CreatePlaneHightMeshFlat(float xV, float yV, float xW, float yW, const char* filename)
{
    uint32 length;
    char* fileContents = fw::LoadCompleteFile(filename, &length);
    if (!fileContents)
    {
        return nullptr;
    }

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* pixels = stbi_load_from_memory((unsigned char*)fileContents, length, &width, &height, &channels, 4);
    if (!pixels)
    {
        delete[] fileContents;
        return nullptr;
    }

    float maxHight = 1.0f;

    std::vector<VertexFormat_PosUVWave> verts;
    std::vector<uint16> indices;

    std::vector<vec3> positions;
    std::vector<vec2> uvs;
    std::vector<vec3> normal;

    vec2 vertCount(xV, yV);
    vec2 worldSize(xW, yW);

    float stepX = worldSize.x / (vertCount.x - 1);
    float stepY = worldSize.y / (vertCount.y - 1);

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {
            vec2 uv = vec2(x * stepX, y * stepY);
            vec2 vertsPos(x * stepX, y * stepY); //- (yW / 2) if want centered to 0,0

            int pixelX = (int)(x * (width - 1) / (vertCount.x - 1));
            int pixelY = (int)(y * (height - 1) / (vertCount.y - 1));

            unsigned char* pixel = &pixels[(pixelY * width + pixelX) * channels];
            float brightness = (pixel[0] + pixel[1] + pixel[2]) / 3.0f / 255.0f;
            float heightValue;// = pow(brightness, 2) * maxHight;

            if (brightness > 0.5f)
            {
                heightValue = maxHight;
            }
            else 
            {
                heightValue = pow(brightness, 2) * maxHight;
            }

            vec3 pos = vec3(vertsPos.x, heightValue, vertsPos.y);

            positions.push_back(pos);
            uvs.push_back(uv);
        }
    }

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {

            vec3 up;
            vec3 down;
            vec3 left;
            vec3 right;

            if (y - 1 >= 0)
            {
                down = positions[x + (y - 1) * vertCount.x];
            }
            else
            {
                down = positions[x + y * vertCount.x];
            }

            if (y + 1 < vertCount.y)
            {
                up = positions[x + (y + 1) * vertCount.x];
            }
            else
            {
                up = positions[x + y * vertCount.x];
            }

            if (x - 1 >= 0)
            {
                left = positions[(x - 1) + y * vertCount.x];
            }
            else
            {
                left = positions[x + y * vertCount.x];
            }

            if (x + 1 < vertCount.x)
            {
                right = positions[(x + 1) + y * vertCount.x];
            }
            else
            {
                right = positions[x + y * vertCount.x];
            }

            vec3 upDir = up - down;
            vec3 rightDir = left - right;

            vec3 normal = rightDir.Cross(upDir);

            vec3 pos = positions[x + y * vertCount.x];
            vec2 uv = uvs[x + y * vertCount.x];

            verts.push_back({ pos, normal, uv });
        }
    }

    for (int y = 0; y < vertCount.y - 1; y++)
    {
        for (int x = 0; x < vertCount.x - 1; x++)
        {
            float bottomLeftIndex = y * vertCount.x + x;

            indices.push_back(bottomLeftIndex + 0.0f);
            indices.push_back(bottomLeftIndex + vertCount.x);
            indices.push_back(bottomLeftIndex + vertCount.x + 1.0f);

            indices.push_back(bottomLeftIndex + 0.0f);
            indices.push_back(bottomLeftIndex + vertCount.x + 1.0f);
            indices.push_back(bottomLeftIndex + 1.0f);
        }
    }

    int vertBytes = sizeof(VertexFormat_PosUVWave) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    fw::Mesh* meshNew = new fw::Mesh(VertexFormat_PosUVWave::format, verts.data(), vertBytes, indices.data(), indicesBytes);

    meshNew->setX(xV);
    meshNew->setZ(yV);
    meshNew->setPos(positions);
    meshNew->setSize(worldSize);

    return meshNew;
}

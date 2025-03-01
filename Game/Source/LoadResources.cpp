//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "DataTypes.h"
#include "Game.h"
#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"

#define getMesh pResources->Get<fw::Mesh>
#define getShader pResources->Get<fw::ShaderProgram>
#define getTexture pResources->Get<fw::Texture>
#define getMaterial pResources->Get<fw::Material>

void LoadResources(fw::ResourceManager* pResources)
{
    // Create some meshes.
    pResources->Add<fw::Mesh>( "Triangle", CreateTriangleMesh() );
    pResources->Add<fw::Mesh>( "Square", CreateSquareMesh() );
    pResources->Add<fw::Mesh>( "Sprite", CreateSpriteMesh() );
    pResources->Add<fw::Mesh>("Cube", CreateCubeMesh());
    pResources->Add<fw::Mesh>("Dice", CreateDiceMesh());
    pResources->Add<fw::Mesh>("Circle", CreateCircleMesh());
    pResources->Add<fw::Mesh>("RightTriangle", CreateRightTriangleMesh());
    pResources->Add<fw::Mesh>("RightTriangleFliped", CreateRightTriangleMeshFliped());

    pResources->Add<fw::Mesh>("Plane", CreatePlaneMesh(5, 5, 10, 10));
    pResources->Add<fw::Mesh>("WaterPlane", CreatePlaneMesh(100, 100, 20, 20));
    pResources->Add<fw::Mesh>("Land", CreatePlaneHightMesh(32, 32, 10, 10, "Data/Textures/IslandHightMap.png"));
    pResources->Add<fw::Mesh>("LandFlat", CreatePlaneHightMeshFlat(32, 32, 10, 10, "Data/Textures/IslandHightMap.png"));

    pResources->Add<fw::Mesh>("ShipHull", CreateShipHullMesh());
    pResources->Add<fw::Mesh>("ShipThruster", CreateShipThrusterMesh());
    pResources->Add<fw::Mesh>("ShipFire", CreateShipFireMesh());
    pResources->Add<fw::Mesh>("ShipLeg", CreateShipLegMesh());

    pResources->Add<fw::Mesh>("Tree", CreateObj("Data/Obj/tree.obj"));
    pResources->Add<fw::Mesh>("RectObj", CreateObj("Data/Obj/Rect.obj"));
    pResources->Add<fw::Mesh>("TeaPot", CreateObj("Data/Obj/TeaPot.obj"));
    pResources->Add<fw::Mesh>("TreeStanding", CreateObj("Data/Obj/TreeRightSideUp.obj"));
    pResources->Add<fw::Mesh>("PlayerPot", CreateObj("Data/Obj/UpRightTeaPot.obj"));

    pResources->Add<fw::Mesh>("Ball", CreateObj("Data/Obj/Ball.obj"));
    pResources->Add<fw::Mesh>("Hole", CreateObj("Data/Obj/Hole.obj"));

    // Load some shaders.
    pResources->Add<fw::ShaderProgram>( "SolidColor", new fw::ShaderProgram( "Data/Shaders/", "SolidColor.vert.bin", "SolidColor.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "VertexColor", new fw::ShaderProgram( "Data/Shaders/", "VertexColor.vert.bin", "VertexColor.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "Texture", new fw::ShaderProgram( "Data/Shaders/", "Texture.vert.bin", "Texture.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "WaterTexture", new fw::ShaderProgram("Data/Shaders/", "WaveVert.vert.bin", "WaveVert.frag.bin"));
    pResources->Add<fw::ShaderProgram>("Hight", new fw::ShaderProgram("Data/Shaders/", "Hight.vert.bin", "Hight.frag.bin"));
    pResources->Add<fw::ShaderProgram>("TreeColour", new fw::ShaderProgram("Data/Shaders/", "TreeColour.vert.bin", "TreeColour.frag.bin"));
    pResources->Add<fw::ShaderProgram>("Light", new fw::ShaderProgram("Data/Shaders/", "Lighting.vert.bin", "Lighting.frag.bin"));
    pResources->Add<fw::ShaderProgram>("LightWithTree", new fw::ShaderProgram("Data/Shaders/", "TreeWithLight.vert.bin", "TreeWithLight.frag.bin"));

    // Load some textures.
    pResources->Add<fw::Texture>( "MegaMan", new fw::Texture( "Data/Textures/MegaMan.png" ) );
    pResources->Add<fw::Texture>("Dice", new fw::Texture("Data/Textures/Dice.png"));

    pResources->Add<fw::Texture>("Ship", new fw::Texture("Data/Textures/Ship.png"));
    pResources->Add<fw::Texture>("ShipLit", new fw::Texture("Data/Textures/ShipLit.png"));
    pResources->Add<fw::Texture>("WaterPNG", new fw::Texture("Data/Textures/Water.png"));
    pResources->Add<fw::Texture>("Grass", new fw::Texture("Data/Textures/Grass.png"));

    // Create some materials.
    pResources->Add<fw::Material>( "Red", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Red(), false ) );
    pResources->Add<fw::Material>( "Blue", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Blue(), false ) );
    pResources->Add<fw::Material>( "Green", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Green(), false ) );
    pResources->Add<fw::Material>("White", new fw::Material(getShader("SolidColor"), nullptr, fw::color4f::White(), false));
    pResources->Add<fw::Material>("Yellow", new fw::Material(getShader("SolidColor"), nullptr, fw::color4f::Yellow(), false));
    pResources->Add<fw::Material>("Orange", new fw::Material(getShader("SolidColor"), nullptr, fw::color4f::Orange(), false));
    pResources->Add<fw::Material>("Cyan", new fw::Material(getShader("SolidColor"), nullptr, fw::color4f::Cyan(), false));

    pResources->Add<fw::Material>( "VertexColor", new fw::Material( getShader("VertexColor"), nullptr, fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "MegaMan", new fw::Material( getShader("Texture"), getTexture("MegaMan"), fw::color4f::White(), true ) );
    pResources->Add<fw::Material>("Dice", new fw::Material(getShader("Texture"), getTexture("Dice"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("Ship", new fw::Material(getShader("Texture"), getTexture("Ship"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("ShipLit", new fw::Material(getShader("Texture"), getTexture("ShipLit"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("Water", new fw::Material(getShader("WaterTexture"), getTexture("WaterPNG"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("HightMap", new fw::Material(getShader("Hight"), getTexture("Grass"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("WaterNoWave", new fw::Material(getShader("Texture"), getTexture("WaterPNG"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("TreeColourMat", new fw::Material(getShader("TreeColour"), getTexture("WaterPNG"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("NullMat", new fw::Material(getShader("Light"), nullptr, fw::color4f::White(), true));

    pResources->Add<fw::Material>("GrassWithLight", new fw::Material(getShader("Light"), getTexture("Grass"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("TreeWithLight", new fw::Material(getShader("LightWithTree"), nullptr, fw::color4f::White(), true));
    pResources->Add<fw::Material>("WaterTexWithLight", new fw::Material(getShader("Light"), getTexture("WaterPNG"), fw::color4f::White(), true));
}

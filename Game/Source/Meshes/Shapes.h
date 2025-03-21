//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "DataTypes.h"
#include "VertexFormats.h"

fw::Mesh* CreateTriangleMesh();
fw::Mesh* CreateSquareMesh();
fw::Mesh* CreateSpriteMesh();

fw::Mesh* CreateRightTriangleMesh();
fw::Mesh* CreateRightTriangleMeshFliped();

fw::Mesh* CreateCircleMesh();

fw::Mesh* CreateCubeMesh();
fw::Mesh* CreateDiceMesh();
fw::Mesh* CreateCubeMesh();

fw::Mesh* CreateShipHullMesh();
fw::Mesh* CreateShipThrusterMesh();
fw::Mesh* CreateShipFireMesh();
fw::Mesh* CreateShipLegMesh();

fw::Mesh* CreatePlaneMesh(float xV, float yV, float xW, float yW);
fw::Mesh* CreatePlaneHightMesh(float xV, float yV, float xW, float yW, const char* filename);
fw::Mesh* CreateObj(const char* fileName);

fw::Mesh* CreatePlaneHightMeshFlat(float xV, float yV, float xW, float yW, const char* filename);
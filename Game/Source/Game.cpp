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
#include "LoadResources.h"
#include "Objects/Player.h"
#include "Events/GameEvents.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "Objects\VirtualController.h" 
#include "Scenes/DemoScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/Box2DScene.h"
#include "Scenes/PinBallScene.h"
#include "Scenes/Midterm.h"
#include "Scenes/MoonLanding.h"
#include "Scenes/CericalGameScene.h"
#include "Scenes/IslandScene.h"
#include "Scenes/LightTest.h"
#include "Scenes/Final.h"

Game::Game(fw::FWCore& fwCore)
    : GameCore( fwCore )
{
    // General renderer settings.
    int viewID = 0;
    bgfx::setViewClear( viewID, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0 );
    bgfx::setViewRect( viewID, 0, 0, m_FWCore.GetWindowClientWidth(), m_FWCore.GetWindowClientHeight() );

    // Create some manager objects.
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore, 1 );
    m_pResources = new fw::ResourceManager();

    // Create uniforms.
    CreateUniforms();

    // Create vertex formats.
    InitVertexFormats();

    // Load Resources.
    LoadResources( m_pResources );

    m_pEventManager = m_EventManager;

    m_Scenes.push_back(new DemoScene(this));
    m_Scenes.push_back(new CubeScene(this));
    m_Scenes.push_back(new Box2DScene(this));
    m_Scenes.push_back(new PinBallScene(this));
    m_Scenes.push_back(new MidtermScene(this));
    m_Scenes.push_back(new MoonLandingScene(this));
    m_Scenes.push_back(new IslandScene(this));
    m_Scenes.push_back(new LightTest(this));

    m_ActiveScene = m_Scenes.back();
}

Game::~Game()
{
    delete m_pResources;
    delete m_pUniforms;

    delete m_pImGuiManager;

    delete m_EventManager;

    //delete the scenes
}

void Game::CreateUniforms()
{
    assert( m_pUniforms == nullptr );

    m_pUniforms = new fw::Uniforms();

    m_pUniforms->CreateUniform("u_MatWorld", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatView", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatProj", bgfx::UniformType::Mat4);

    m_pUniforms->CreateUniform( "u_DiffuseColor", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_TextureColor", bgfx::UniformType::Sampler );
    m_pUniforms->CreateUniform( "u_UVScale", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_UVOffset", bgfx::UniformType::Vec4 );

    m_pUniforms->CreateUniform( "u_Time", bgfx::UniformType::Vec4 );

    m_pUniforms->CreateUniform("u_LightColour", bgfx::UniformType::Vec4);
    m_pUniforms->CreateUniform("u_LightPos", bgfx::UniformType::Vec4);
    m_pUniforms->CreateUniform("u_LightRange", bgfx::UniformType::Vec4);

    m_pUniforms->CreateUniform("u_LightAmbientPer", bgfx::UniformType::Vec4);
    m_pUniforms->CreateUniform("u_LightFalloff", bgfx::UniformType::Vec4);

    m_pUniforms->CreateUniform("u_MatWorldRotation", bgfx::UniformType::Mat4);
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );

    if (m_ActiveScene->getVirtualController() != nullptr)
    {
        VirtualController* virtualController = m_ActiveScene->getVirtualController();
        virtualController->StartFrame();
    }
    
    m_pEventManager->processEvents();
}

void Game::OnEvent(fw::Event* pEvent)
{
    // Process events.
    if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
    {
        if (m_ActiveScene->getVirtualController() != nullptr)
        {
            VirtualController* virtualController = m_ActiveScene->getVirtualController();
            virtualController->OnEvent(pEvent);
        }
    }

    // Set the new aspect ratio in the camera.
    if( pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType() )
    {
        int width = m_FWCore.GetWindowClientWidth();
        int height = m_FWCore.GetWindowClientHeight();


        if (m_ActiveScene->getCamera() != nullptr)
        {
            fw::Camera* camera = m_ActiveScene->getCamera();
            camera->SetAspectRatio( (float)width/height );
        }
    }

    if (pEvent->GetType() == ColisionGameEvent::GetStaticEventType())
    {
        m_ActiveScene->OnEvent(pEvent);
    }

    // Pass "WM_CHAR" events to imgui to handle text input.
    if( pEvent->GetType() == fw::CharEvent::GetStaticEventType() )
    {
        int character = static_cast<fw::CharEvent*>(pEvent)->GetValue();
        m_pImGuiManager->AddInputCharacter( character );
    }
}

void Game::Update(float deltaTime)
{
    m_ActiveScene->Update(deltaTime);

    Editor_DisplayObjectList();
    Editor_DisplayResources();
    Editor_DisplayScene();
}

void Game::Draw()
{
    // Setup time uniforms.
    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform( m_pUniforms->GetUniform("u_Time"), &time );

    m_ActiveScene->Draw();

    m_pImGuiManager->EndFrame();
}

void Game::Editor_DisplayObjectList()
{
    ImGui::Begin( "Object List" );

    for( fw::GameObject* pObject : m_ActiveScene->getObjects())
    {
        ImGui::Text( "%s", pObject->GetName().c_str() );
    }
    if (CubeScene* cubeScene = dynamic_cast<CubeScene*>(m_ActiveScene)) //if the scene is a cube scene do this
    {
        float spinSpeed = cubeScene->getSpeed();
        ImGui::InputFloat("Spin Speed", &spinSpeed);

        cubeScene->setSpeed(spinSpeed);
    }

    // Testing character input, get rid of this once you confirm its working.

    ImGui::End(); // "Object List"
}

void Game::Editor_DisplayResources()
{
    ImGui::Begin("Resources");

    m_pResources->Editor_DisplayResourceLists();

    ImGui::End(); // "Resources"
}

void Game::Editor_DisplayScene()
{
    ImGui::Begin("Scenes");

    //show what scene your in, then created scenas
    ImGui::Text("%s", "Current Scene:");

    ImGui::Text("   %s", m_ActiveScene->GetName().c_str());

    ImGui::Text("%s", "Other Scenes:");

    for (fw::Scene* pScene : m_Scenes)
    {
        if (ImGui::Button(pScene->GetName().c_str()))
        {
            m_ActiveScene = pScene;
        }
    }

    ImGui::End();
}

void Game::Editor_DisplayCustomPopUp(std::string name, std::string& data)
{
    ImGui::Begin(name.c_str());

    // Show what scene you're in, then created scenes
    if (!data.empty())
    {
        ImGui::Text("%s", data.c_str());
    }

    ImGui::End();
}

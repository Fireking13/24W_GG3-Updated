#include "VirtualController.h"

VirtualController::VirtualController()
{
	// register for imput events
}

VirtualController::~VirtualController()
{

}

void VirtualController::OnEvent(fw::Event* pEvent)
{
	// Code to set controls based on events.
	if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
	{
		fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>(pEvent);

		if (pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard)
		{
			if (pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
			{
				switch (pInputEvent->GetKeyCode())
				{
				case 'W': case VK_UP: { m_Actions = m_Actions | Actions::Up; } break;
				case 'A': case VK_LEFT: { m_Actions = m_Actions | Actions::Left; } break;
				case 'S': case VK_DOWN: { m_Actions = m_Actions | Actions::Down; } break;
				case 'D': case VK_RIGHT: { m_Actions = m_Actions | Actions::Right; } break;
				case VK_SPACE: { m_Actions = m_Actions | Actions::Jump; } break;
				case 'Z': { m_Actions = m_Actions | Actions::Teleport; } break;
				case 'R': { m_Actions = m_Actions | Actions::Reset; } break;
				case 'I': { m_Actions = m_Actions | Actions::LookUp; } break;
				case 'K': { m_Actions = m_Actions | Actions::LookDown; } break;
				case 'J': { m_Actions = m_Actions | Actions::LookLeft; } break;
				case 'L': { m_Actions = m_Actions | Actions::LookRight; } break;
				case 'U': { m_Actions = m_Actions | Actions::ZoomIn; } break;
				case 'M': { m_Actions = m_Actions | Actions::ZoomOut; } break;

				}
			}

			if (pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
			{
				switch (pInputEvent->GetKeyCode())
				{
				case 'W': case VK_UP: { m_Actions = m_Actions & ~Actions::Up; } break;
				case 'A': case VK_LEFT: { m_Actions = m_Actions & ~Actions::Left; } break;
				case 'S': case VK_DOWN: { m_Actions = m_Actions & ~Actions::Down; } break;
				case 'D': case VK_RIGHT: { m_Actions = m_Actions & ~Actions::Right; } break;
				case VK_SPACE: { m_Actions = m_Actions & ~Actions::Jump; } break;
				case 'Z': { m_Actions = m_Actions & ~Actions::Teleport; } break;
				case 'R': { m_Actions = m_Actions & ~Actions::Reset; } break;
				case 'I': { m_Actions = m_Actions & ~Actions::LookUp; } break;
				case 'K': { m_Actions = m_Actions & ~Actions::LookDown; } break;
				case 'J': { m_Actions = m_Actions & ~Actions::LookLeft; } break;
				case 'L': { m_Actions = m_Actions & ~Actions::LookRight; } break;
				case 'U': { m_Actions = m_Actions & ~Actions::ZoomIn; } break;
				case 'M': { m_Actions = m_Actions & ~Actions::ZoomOut; } break;
				}
			}
		}
	}
}

void VirtualController::StartFrame()
{
	m_OldActions = m_Actions;
}



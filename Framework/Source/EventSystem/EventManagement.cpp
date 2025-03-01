#include "EventManagement.h"

namespace fw {

	EventManagement::EventManagement(GameCore* gameCore)
	{
		m_pGame = gameCore;
	}

	EventManagement::~EventManagement()
	{
	}

	void EventManagement::addEvent(Event* events)
	{
		m_Queue.push(events);
	}

	void EventManagement::processEvents()
	{
		while (!m_Queue.empty())
		{
			Event* pEvent = m_Queue.front();
			m_Queue.pop();

			m_pGame->OnEvent(pEvent);
			delete pEvent;
		}
	}
}
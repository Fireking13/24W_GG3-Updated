#pragma once
#include "Events.h"
#include "GameCore.h"
#include <queue>

namespace fw {

    class EventManagement
    {
    public:
        EventManagement(GameCore* gameCore);
        virtual ~EventManagement();

        void addEvent(Event* events);
        void processEvents();

    private:
    protected:
        std::queue<Event*> m_Queue;
        GameCore* m_pGame;
    };
}
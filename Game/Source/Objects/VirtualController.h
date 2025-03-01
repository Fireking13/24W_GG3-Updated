#pragma once

#include "DataTypes.h"

class VirtualController
{
public:
    enum Actions
    {
        Teleport = 1 << 0,
        Up = 1 << 1,
        Down = 1 << 2,
        Left = 1 << 3,
        Right = 1 << 4,
        Jump = 1 << 5,
        Reset = 1 << 6,
        LookUp = 1 << 7,
        LookDown = 1 << 8,
        LookLeft = 1 << 9,
        LookRight = 1 << 10,
        ZoomIn = 1 << 11,
        ZoomOut = 1 << 12,
    };

public:
    VirtualController();
    virtual ~VirtualController();

    void OnEvent(fw::Event* pEvent);

    void StartFrame();

    bool IsActionHeld(Actions action) { return (m_Actions & action ); }
    bool IsActionPressed(Actions action) { return (m_Actions & action && !(m_OldActions & action)); } //to do
    bool IsActionReleased(Actions action) { return (!(m_Actions & action) && m_OldActions & action); } //to do

protected:
    uint32 m_Actions = 0;
    uint32 m_OldActions = 0;
    };

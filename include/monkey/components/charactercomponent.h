#pragma once

#include <gfx/components/statemachine2.h>

enum class Direction { EAST, WEST, NORTH, SOUTH };

class StateCharacter : public StateMachine2 {
public:
    StateCharacter() : StateMachine2() {}
    void SetDirection(Direction dir);
private:
    Direction m_dir;
};
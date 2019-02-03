#pragma once

#include <gfx/components/statemachine2.h>

enum class Direction { EAST, WEST, NORTH, SOUTH };

class DirectionBuilder {
public:
    static Direction FromString(const std::string&) {
        return Direction::EAST;
    }
    
};


class StateCharacter : public StateMachine2 {
public:
    StateCharacter() : StateMachine2() {}
    void SetDirection(Direction dir);
private:
    Direction m_dir;
};

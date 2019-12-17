#include "jump.h"

Jump::Jump() : State(){}

Jump::Jump(const Jump &orig) : State(orig) {}

std::shared_ptr<State> Jump::clone() const {
    return std::make_shared<Jump>(*this);
}

void Jump::Init() {
    m_entity = m_sm->GetObject();
}

void Jump::Run(double dt) {

}

void Jump::End() {
}


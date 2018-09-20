#pragma once

#include <gfx/component.h>
#include <vector>

// used for mutually exclusive entities
class Switch : public Component {
public:
    Switch(const std::vector<std::string>& states, const std::string& initial) : Component(), m_stateNames(states), m_initialState(initial) {}
    void Start() override;
    void Update(double) override {}
    void ChangeState(const std::string&);
    using ParentClass = Switch;
private:
    std::string m_currentlyActive;
    std::unordered_map<std::string, Entity*> m_states;
    std::vector<std::string> m_stateNames;
    std::string m_initialState;
};
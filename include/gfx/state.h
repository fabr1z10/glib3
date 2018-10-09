#pragma once

#include <string>
#include <memory>

class Entity;

class StateInitializer {
public:
    virtual void Init(Entity*) = 0;
    virtual void Start() = 0;
};

class StateBehaviour {
public:
    virtual void ResetState() {}
    virtual void Init(Entity*) = 0;
    virtual bool Run(double) = 0;
protected:
    std::string m_nextState;
};



class State {
public:
    State() : m_nextState() {}
    void Init(Entity*);
    void Start();
    bool Run(double);
    std::string GetNextState() const;
    std::string GetId() const;
    void SetId(const std::string& id);
    void SetInitializer(std::unique_ptr<StateInitializer>);
    void SetBehaviour(std::unique_ptr<StateBehaviour>);
protected:
    std::unique_ptr<StateInitializer> m_initializer;
    std::unique_ptr<StateBehaviour> m_behaviour;
    std::string m_id;
    std::string m_nextState;
    Entity* m_entity;
};

inline std::string State::GetNextState() const {
    return m_nextState;
}

inline std::string State::GetId() const {
    return m_id;
}

inline void State::SetId(const std::string& id) {
    m_id = id;
}

inline void State::SetInitializer(std::unique_ptr<StateInitializer> init) {
    m_initializer = std::move(init);
}

inline void State::SetBehaviour(std::unique_ptr<StateBehaviour> behavior) {
    m_behaviour = std::move(behavior);
}
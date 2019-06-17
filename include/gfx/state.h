//#pragma once
//
//#include <string>
//#include <memory>
//#include <gfx/lua/luawrapper.h>
//
//class Entity;
//
//class StateInitializer {
//public:
//    virtual ~StateInitializer() {}
//    virtual void Init(Entity*) = 0;
//    virtual void Start() = 0;
//    // init with params
//    virtual void Start(luabridge::LuaRef) {
//        Start();
//    }
//};
//
//class StateBehaviour {
//public:
//    virtual ~StateBehaviour() {}
//    virtual void ResetState() {}
//    virtual void ResetState(luabridge::LuaRef) {}
//    virtual void Init(Entity*) = 0;
//    virtual bool Run(double) = 0;
//    std::string GetNextState() const;
//protected:
//    std::string m_nextState;
//};
//
//
//
//inline std::string StateBehaviour::GetNextState() const {
//    return m_nextState;
//}
//
//class State {
//public:
//    State() : m_finalizer(nullptr), m_behaviour(nullptr), m_initializer(nullptr), m_entity(nullptr) {}
//    void Init(Entity*);
//    void Start();
//    void Start(luabridge::LuaRef param);
//    bool Run(double);
//    void End();
//    std::string GetNextState() const;
//    std::string GetId() const;
//    void SetId(const std::string& id);
//    void SetInitializer(std::unique_ptr<StateInitializer>);
//    void SetBehaviour(std::unique_ptr<StateBehaviour>);
//    void SetFinalizer(std::unique_ptr<StateInitializer>);
//protected:
//    std::unique_ptr<StateInitializer> m_initializer;
//    std::unique_ptr<StateBehaviour> m_behaviour;
//    std::unique_ptr<StateInitializer> m_finalizer;
//    std::string m_id;
//    Entity* m_entity;
//};
//
//inline std::string State::GetNextState() const {
//    return m_behaviour->GetNextState();
//}
//
//inline std::string State::GetId() const {
//    return m_id;
//}
//
//inline void State::SetId(const std::string& id) {
//    m_id = id;
//}
//
//inline void State::SetInitializer(std::unique_ptr<StateInitializer> init) {
//    m_initializer = std::move(init);
//}
//
//inline void State::SetBehaviour(std::unique_ptr<StateBehaviour> behavior) {
//    m_behaviour = std::move(behavior);
//}
//
//inline void State::SetFinalizer(std::unique_ptr<StateInitializer> finalizer) {
//    m_finalizer = std::move(finalizer);
//}
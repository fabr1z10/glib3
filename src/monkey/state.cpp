//#include <monkey/state.h>
//
//void State::Init(Entity* e) {
//    if (m_initializer != nullptr)
//        m_initializer->Init(e);
//    if (m_behaviour != nullptr)
//        m_behaviour->Init(e);
//    if (m_finalizer != nullptr)
//        m_finalizer->Init(e);
//}
//
//void State::Start() {
//    if (m_initializer != nullptr)
//        m_initializer->Start();
//    if (m_behaviour != nullptr)
//        m_behaviour->ResetState();
//
//}
//
//void State::Start(luabridge::LuaRef param) {
//    if (m_initializer != nullptr)
//        m_initializer->Start(param);
//    if (m_behaviour != nullptr)
//        m_behaviour->ResetState(param);
//}
//
//
//void State::End() {
//    if (m_finalizer != nullptr)
//        m_finalizer->Start();
//}
//
//bool State::Run(double dt) {
//    if (m_behaviour != nullptr)
//        return m_behaviour->Run(dt);
//    return false;
//}

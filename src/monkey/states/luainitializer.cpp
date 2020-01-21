//#include <monkey/states/luainitializer.h>
//#include <monkey/entitywrapper.h>
//
//LuaInitializer::LuaInitializer (luabridge::LuaRef ref) : StateInitializer(), m_ref(ref) {
//
//}
//
//
//void LuaInitializer::Init(Entity* e) {
//    m_entity = e;
//}
//
//void LuaInitializer::Start () {
//    m_ref(EntityWrapper(m_entity));
//}
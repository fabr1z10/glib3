//#include <gfx/basicfactory.h>
//#include <gfx/monkey.h>
//#include <iostream>
//#include <gfx/spritemesh.h>
//#include <glm/gtx/transform.hpp>
//#include <gfx/math/geom.h>
//
////#include <mo/components/scriptwalktrigger.h>
//
//using namespace luabridge;
//
//BasicSceneFactory::BasicSceneFactory() {
//
//    m_entityFactory.Add<EntityFactory>("default");
//    m_entityFactory.Add<OutlineTextFactory>("outlinetext");
//
//    m_componentFactory.Add<TextComponentFactory>("text");
//    m_componentFactory.Add<GfxComponentFactory>("gfx");
//    m_componentFactory.Add<ColliderComponentFactory>("collider");
//    m_componentFactory.Add<StateMachineComponentFactory>("statemachine");
//    m_componentFactory.Add<DepthComponentFactory>("depth");
//    m_componentFactory.Add<InfoComponentFactory>("info");
//    m_componentFactory.Add<FollowComponentFactory>("follow");
//    m_componentFactory.Add<HotSpotComponentFactory>("hotspot");
//    m_componentFactory.Add<Controller2DComponentFactory>("controller2d");
//    m_componentFactory.Add<Dynamics2DComponentFactory>("dynamics2d");
//
//    m_cameraFactory.Add<OrthoCamFactory>("ortho");
//    m_cameraFactory.Add<PerspectiveCamFactory>("perspective");
//
//
//
//
////    AddFactory<KeyInputFactory>("keyinput");
////    AddFactory<HotSpotComponentFactory>("hotspot");
////    AddFactory<LuaKeyboardComponentFactory>("luakey");
////
////    AddFactory<BillboardComponentFactory>("billboard");
////    AddFactory<ButtonComponentFactory>("button");
////    AddFactory<TextViewComponentFactory>("textview");
////    AddFactory<ShadowComponentFactory>("shadow");
//
//

//
//    m_activityFactory.Add<NoOpActFactory>("noop");
//    m_activityFactory.Add<ChangeRoomActFactory>("gotoroom");
//
//
//
////    m_stateFactories["basic"] = std::make_shared<BasicStateFactory>();
////    m_stateFactories["walk"] = std::make_shared<WalkStateFactory>();
////    m_stateFactories["aiwalk"] = std::make_shared<AIWalkStateFactory>();
////    m_stateFactories["walkcollision"] = std::make_shared<WalkCollisionStateFactory>();
////    m_stateFactories["hit"] = std::make_shared<HitStateFactory>();
//
//    m_specialKeys.insert("tag");
//    m_specialKeys.insert("name");
//    m_specialKeys.insert("pos");
//    m_specialKeys.insert("angle");
//    m_specialKeys.insert("children");
//    m_specialKeys.insert("active");
//}
//
//
//
//
//
//
//std::shared_ptr<Entity> BasicSceneFactory::ReadItem(luabridge::LuaRef& ref) {
//    LuaTable item(ref);
//    auto entity = std::make_shared<Entity>();
//    std::string tag = item.Get<std::string>("tag", "");
//    std::string name = item.Get<std::string>("name", "");
//    if (!tag.empty()) entity->SetTag(tag);
//    if (!name.empty()) entity->SetName(name);
//    glm::vec3 pos = item.Get<glm::vec3>("pos", glm::vec3(0.0f));
//    bool active = item.Get<bool>("active", true);
//    if (item.HasKey("angle")) {
//        float angle = item.Get<float>("angle",0.0f);
//        entity->SetPosition(pos, deg2rad* angle);
//    } else {
//        entity->SetPosition(pos);
//    }
//
//
//    // int layer = item.Get<int>("layer", 0);
//
//
//    auto keyValueMap = LuaTable::getKeyValueMap(ref);
//    for (auto& pair : keyValueMap) {
//        auto iter = m_componentFactories.find(pair.first);
//        //std::cout << "Reading " << pair.first << "\n";
//        if (iter == m_componentFactories.end()) {
//            if (m_specialKeys.count(pair.first) == 0) {
//                GLIB_FAIL("Unknown component " << pair.first);
//            }
//        } else {
//            iter->second->operator()(pair.second, entity.get());
//        }
//    }
//
//
//    if (item.HasKey("children")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
//        ReadItems (c, entity.get());
//    }
//    //entity->SetActive(active);
//    return entity;
//
//
//}
//
//
//void BasicSceneFactory::ReadItems(luabridge::LuaRef& scene, Entity* parent) {
//    for (int i = 0; i < scene.length(); ++i) {
//        // create new entity
//        luabridge::LuaRef r = scene[i+1];
//        auto entity = Get<Entity>(r);
//        //auto entity = ReadItem(r);
//        parent->AddChild(entity);
//    }
//
//
//
//
//}
//
//
//
//
//void BasicSceneFactory::PostInit() {
//
//    // Create the local assets
//    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
//    LuaTable roomTable(roomRef);
//    if (roomTable.HasKey("afterstartup")) {
//        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("afterstartup");
//        r1();
//    }
//}
//
//

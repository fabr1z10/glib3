//#include "monkey/skeletal/skeletalcollidermanager.h"
//#include "monkey/engine.h"
//
//
//SkeletalColliderManager::SkeletalColliderManager(const ITable & t) {
//
//	auto factory = Engine::get().GetSceneFactory();
//
//	t.foreach<PyTable> ("colliders", [&] (const PyTable& table) {
//		auto collider = factory->make2<SkColl> (table);
//		m_colliders.push_back(collider);
//	});
//
//}
//
//void SkeletalColliderManager::Start() {
//
//	for (const auto& collider : m_colliders) {
//		collider->SetParent( m_entity);
//		collider->Start();
//	}
//}
//
//void SkeletalColliderManager::Update(double dt) {
//	for (const auto& collider : m_colliders) {
//		collider->Update(dt);
//	}
//
//}
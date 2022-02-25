#include <monkey/icollisionengine.h>
#include <monkey/luacollision.h>

namespace py = pybind11;

ICollisionEngine::ICollisionEngine(const ITab& table) : Runner(table) {
	auto crm = std::make_unique<CollisionResponseManager>();
	if (table.has("response")) {
        table.foreach("response", [&](const ITab &p) {
            auto tag0 = p.get<int>("tag1");
            auto tag1 = p.get<int>("tag2");
            //PyTable t(p[2].cast<py::object>());
            auto l = std::make_unique<LuaCollisionResponse>();
            //auto response = p["response"];
            if (p.has("on_enter")) {
                auto f = p.get<py::function>("on_enter");
                l->setOnEnter(f);
            }
            if (p.has("on_leave")) {
                auto f = p.get<py::function>("on_leave");
                l->setOnLeave(f);
            }
            if (p.has("on_stay")) {
                auto f = p.get<py::function>("on_stay");
                l->setOnStay(f);
            }
            crm->AddCollisionResponse(tag0, tag1, std::move(l));
        });
        SetResponseManager(std::move(crm));
    }
}

ICollisionEngine::ICollisionEngine() : Runner(), m_responseManager(nullptr) {
}

void ICollisionEngine::SetResponseManager(std::unique_ptr<CollisionResponseManager> r){
    m_responseManager = std::move(r);
}

CollisionResponseManager* ICollisionEngine::GetResponseManager() {
    return m_responseManager.get();
}

void ICollisionEngine::processCollisions(const std::vector<ShapeCastHit> & e, Entity* entity, int tag) {
	auto rm = GetResponseManager();
	if (rm == nullptr) {
		return;
	}
	for (const auto& coll : e) {
		auto object = coll.entity->GetObject();
		auto handler = rm->GetHandler(tag, coll.entity->GetCollisionTag());
		if (handler.response != nullptr) {
			if (handler.flip) {
				handler.response->onStart(object, entity, coll.report);
			} else {
				handler.response->onStart(entity, object, coll.report);
			}
		}
	}

}
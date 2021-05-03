#include <monkey/icollisionengine.h>
#include <monkey/luacollision.h>

namespace py = pybind11;

ICollisionEngine::ICollisionEngine(const ITab& table) : Runner(table) {
	auto crm = std::make_unique<CollisionResponseManager>();
	table.foreach("response", [&] (const ITab& p) {
		auto tag0 = p.get<int>("tag1");
		auto tag1 = p.get<int>("tag2");
		//PyTable t(p[2].cast<py::object>());
		auto l = std::make_unique<LuaCollisionResponse>();
		auto response = p["response"];
		if (response->has("on_enter")) {
			auto f = response->get<py::function>("on_enter");
			l->setOnEnter(f);
		}
		if (response->has("on_leave")) {
			auto f = response->get<py::function>("on_leave");
			l->setOnLeave(f);
		}
		if (response->has("on_stay")) {
			auto f = response->get<py::function>("on_stay");
			l->setOnStay(f);
		}
		crm->AddCollisionResponse(tag0, tag1, std::move(l));
	});
	SetResponseManager(std::move(crm));
}

ICollisionEngine::ICollisionEngine() : Runner(), m_responseManager(nullptr) {
}

void ICollisionEngine::SetResponseManager(std::unique_ptr<CollisionResponseManager> r){
    m_responseManager = std::move(r);
}

CollisionResponseManager* ICollisionEngine::GetResponseManager() {
    return m_responseManager.get();
}
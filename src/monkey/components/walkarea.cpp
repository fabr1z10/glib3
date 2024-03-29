#include <monkey/components/walkarea.h>
#include <GLFW/glfw3.h>
#include <monkey/scheduler.h>

#include <monkey/engine.h>
#include <iostream>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/shortestpath.h>
#include <monkey/properties.h>
#include <monkey/meshfactory.h>
#include <monkey/components/renderer.h>
#include <monkey/scenefactory.h>
//WalkArea::WalkArea(std::shared_ptr<IShape> shape, int priority) : ScriptHotSpot(shape, priority) {}

WalkArea::WalkArea(const ITab& t) : Component(t) {
    auto factory = Engine::get().GetSceneFactory();
    auto sh = t["shape"];
    m_shape = factory->make2<IShape>(*sh);
    if (m_shape->getShapeType() == ShapeType::POLY) {
        // polygonal walkarea
        m_shortestPath = std::make_shared<PolygonShortestPath>();
    } else if (m_shape->getShapeType() == ShapeType::POLYLINE) {
        m_shortestPath = std::make_shared<PolyLineShortestPath>();
    } else {
        GLIB_FAIL("Walkareas shape must be poly or polyline.")
    }

    if (t.has("depth")) {
        auto dref = t["depth"];
        auto depthFunc = factory->make2<Function2D>(*dref);
        SetDepthFunction(depthFunc);
    }
    
    if (t.has("scale")) {
        auto dref = t["scale"];
        auto scaleFunc = factory->make2<Function2D>(*dref);
        SetScalingFunction(scaleFunc);
    }

    if (t.has("walls")) {
        t.foreach("walls", [&](const ITab &t) {
            auto a = t.get<glm::vec2>("A");
            auto b = t.get<glm::vec2>("B");
            auto active = t.get<bool>("active");
            m_shortestPath->addWall(a, b, active);
        });
    }
    m_shortestPath->setShape(m_shape);
}

void WalkArea::onAdd(Entity * e) {
//    auto props = e->GetComponent<Properties>();
//    if (props != nullptr) {
//        luabridge::LuaRef scale = props->get("walkarea_scale");
//        if (!scale.isNil()) {
//            bool wsc = scale.cast<bool>();
//            if (!wsc) {
//                assignDepth(e);
//                e->onMove.Register(this, [&] (Entity*) { assignDepth(e); });
//                return;
//            }
//        }
//    }
    assignScaleAndDepth(e);
    e->onMove.Register(this, [&] (Entity* e) { assignScaleAndDepth(e);});

}

void WalkArea::assignDepth (Entity* e) {

    e->setOnMoveEnabled(false);
    glm::vec2 pos = e->GetPosition();
    if (m_depthFunc != nullptr) {
        float z = m_depthFunc->operator()(pos.x, pos.y);

        e->SetZ(z);
        //std::cout << "z is " << e->GetPosition().z << "\n";
    }
    e->setOnMoveEnabled(true);
}


void WalkArea::assignScaleAndDepth (Entity* e) {
    if (m_scaleDepthExclude.count(e) > 0) {
        return;
    }
    e->setOnMoveEnabled(false);
    glm::vec2 pos = e->GetPosition();
    if (m_depthFunc != nullptr) {
        float z = m_depthFunc->operator()(pos.x, pos.y);
        e->SetZ(z);
        //std::cout << "z is " << e->GetPosition().z << "\n";
    }

    if (m_scaleFunc != nullptr) {
        float scale = m_scaleFunc->operator()(pos.x, pos.y);
        e->SetScale(scale);
    }
    e->setOnMoveEnabled(true);
}

//std::shared_ptr<Entity> WalkArea::getDebugMesh() {
//    auto ptr = HotSpot::getDebugMesh();
////    auto props = std::make_shared<Properties>();
////    //return nullptr;
////    luabridge::LuaRef ciao = LuaWrapper::makeTable();
////    ciao["walkarea_scale"] = false;
////    props->addAdditionalProps(ciao);
////    ptr->AddComponent(props);
//    return ptr;
//}

void WalkArea::EnableBlockedLine(int id, bool active) {
    m_shortestPath->setWall(id, active);
}

void WalkArea::recalc() {
    m_shortestPath->updateGraph();
}

void WalkArea::Start() {
    //ScriptHotSpot::Start();

    if (m_depthFunc != nullptr || m_scaleFunc != nullptr) {
        for (const auto &c : m_entity->GetChildren()) {
            for (const auto& d : c.second) {
				onAdd(d.get());
			}
        }
    }
    m_entity->onAdd.Register(this, [&] (Entity* e) { onAdd(e); });
    m_entity->onRemove.Register(this, [&] (Entity* e) {
        e->onMove.Unregister(this);
    });

    // automatically add a collider component. WHY ???
    //auto coll = std::make_shared<SimpleCollider>(m_shape,1,2,1);
    //m_entity->AddComponent(coll);
    //coll->Start();
    if (m_shape != nullptr) {
        auto c = std::make_shared<Entity>();
        c->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));

        m_scaleDepthExclude.insert(c.get());

        MeshFactory m;
        auto model = m.createWireframe(m_shape.get(), glm::vec4(1.0f));
        auto renderer = std::make_shared<Renderer>(model);
        c->AddComponent(renderer);
        m_entity->AddChild(c);
        for (const auto& wall : m_shortestPath->getWalls()) {
            Segment seg(wall.A, wall.B);
            auto d = std::make_shared<Entity>();
            d->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
            auto mod = m.createWireframe(&seg, glm::vec4(1.0f));
            auto rend = std::make_shared<Renderer>(mod);
            d->AddComponent(rend);
            c->AddChild(d);

        }
    }
}

std::vector<glm::vec2> WalkArea::findPath(glm::vec2 A, glm::vec2 B, int& retval) {
    std::vector<glm::vec2> points;
    retval = m_shortestPath->find(A, B, points);
    return points;
}

float WalkArea::checkMove(glm::vec2 A, glm::vec2 dir, float length) {
	RayCast2D ciao;
	glm::vec3 P0(A, 0.0f);
	glm::vec3 P1 = P0 + glm::vec3(dir, 0.0f) * length;
	auto pippo = ciao.run(P0, P1, m_shape.get(), glm::mat4(1.0f));
	if (pippo.collide) {
		std::cout << "FIGAAA!!\n";
		if (pippo.length < 0.1f) {
			return 0.0f;
		}
		return 0.9f* pippo.length;
	}
	return length;

}

//void WalkArea::onClick(glm::vec2 worldCoords, int button, int action, int mods) {
//
//    // here I need to answer this question:
//    // is the character on the same walkarea? (in this case, just a walk)
//    if (action == GLFW_PRESS) {
//        if (m_player->GetParent() != this->m_entity) {
//            std::cout << "Clicking on a different walkarea...";
//            if (m_func != nullptr) {
//
//                m_func->execute(m_player->GetParent()->GetTag(), worldCoords.x, worldCoords.y);
//                return;
//            }
//
//            // see if I have a handler for (from: this, to: that, pos: worldcoords)
//        }
//        auto script = std::make_shared<Script>();
//        script->AddActivity(1, std::unique_ptr<Walk>(new Walk(m_id, worldCoords)));
//        script->AddEdge(0, 1);
//        m_scheduler->AddScript("_walk", script);
//    }
//}

//float WalkArea::GetDepth (float x, float y) {
//    if (m_depthFunc == nullptr)
//        GLIB_FAIL("Depth function not set for this walkarea");
//    return m_depthFunc->operator()(x, y);
//}
//
//float WalkArea::GetScale (float x, float y) {
//    if (m_scaleFunc == nullptr)
//        GLIB_FAIL("Depth function not set for this walkarea");
//    return m_scaleFunc->operator()(x, y);
//}





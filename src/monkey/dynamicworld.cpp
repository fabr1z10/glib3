#include <monkey/dynamicworld.h>
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <iostream>


namespace py = pybind11;

DynamicWorldItem::DynamicWorldItem(const PyTable &table, const Bounds& b, const glm::vec3& pos) :
    m_template(table), m_id(-1), m_alive(false), m_removedByDynamicWorld(false), m_active(true), m_entity(nullptr), m_localBounds(b)
{
    m_initBounds = m_localBounds;
    m_initBounds.Translate(pos);
}

Bounds DynamicWorldItem::getCurrentBounds() const {
    auto localBounds = m_localBounds;
    localBounds.Translate(m_entity->GetPosition());
    return localBounds;

}

std::shared_ptr<Entity> DynamicWorldItem::create() {
    auto factory = Engine::get().GetSceneFactory();
    auto node = factory->make2<Entity>(this->m_template);
    node->onDestroy.Register(this, [&] (Entity* cam) {
        // this is called when the entity is removed
        // now, if the entity has been removed by the dynamic world, then
        m_entity = nullptr;
        m_alive = false;
        if (!m_removedByDynamicWorld) {
            m_active = false;
        }
    });
    m_alive = true;
    m_removedByDynamicWorld = false;
    m_id = node->GetId();
    m_entity = node.get();
    return node;
}

void DynamicWorldItem::destroy() {
    Engine::get().Remove(m_id);
    m_removedByDynamicWorld = true;
}

DynamicWorldBuilder::DynamicWorldBuilder(const ITable &t) : Runner(t), m_x(-1), m_y(-1) {
    m_width = t.get<float>("width");
    m_height = t.get<float>("height");

    m_halfWidth = m_width *0.5f;
    m_halfHeight = m_height * 0.5f;

    m_camName = t.get<std::string>("cam");
    auto factory = Engine::get().GetSceneFactory();
    // get dynamic entities
    t.foreach<py::object>("items", [&] (py::object obj) {
        PyTable table(obj);
        auto node = factory->make2<Entity>(table);
        auto renderer = node->GetComponent<Renderer>();
        glm::vec3 pos = node->GetPosition();
        Bounds bounds;
        if (renderer != nullptr) {
            bounds = renderer->GetBounds();
        } else {
            // TODO
        }
        auto item = std::make_shared<DynamicWorldItem>(table, bounds, pos);
        m_items.push_back(item);
    });
}

DynamicWorldBuilder::~DynamicWorldBuilder() noexcept {

}


void DynamicWorldBuilder::Begin() {
    std::cerr << "INIT DYNAMIC WORLD!\n";
    auto cam = Monkey::get().Get<Camera>(m_camName);
    cam->OnMove.Register(this, [&] (Camera* cam) { this->OnCameraMove(cam); });
    glm::vec3 camPos = cam->GetPosition();
    // inititalize the center
    m_xc0 = camPos.x;
    m_yc0 = camPos.y;
    m_x = -1;
    m_y = -1;
    m_parentEntity = Monkey::get().Get<Entity>("main");
//    m_parentEntity->onRemove.Register(this, [&] (Entity* e) {
//        auto it = m_outBounds.find(e->GetId());
//        if (it != m_outBounds.end()) {
//            // item has been removed by dynamic world
//            m_outBounds.erase(it);
//            return;
//        }
//        std::cerr << "REMOVED EXTERNALLY ENTITY " << e->GetId() << "\n";
//        m_removedItems.insert(e->GetId());
//
//    });
    UpdateWorld(camPos);

}

// this method is called everytime we need to regenerate the world based on cam position
void DynamicWorldBuilder::UpdateWorld(glm::vec3 pos) {

    int ix = static_cast<int>((pos.x - m_xc0) / m_halfWidth + 0.5f);
    int iy = static_cast<int>((pos.y - m_yc0) / m_halfHeight + 0.5f);

    // update the center
    m_xc = m_xc0 + m_halfWidth * ix;
    m_yc = m_yc0 + m_halfHeight * iy;

    // update the inner window (when cam falls outside, triggers an update)
    m_xmin = m_xc - m_halfWidth;
    m_xmax = m_xc + m_halfWidth;
    m_xmin = m_xc - m_halfWidth;
    m_xmax = m_xc + m_halfWidth;

    m_activeBounds.min.x = m_xc - m_width;
    m_activeBounds.min.y = m_yc - m_height;
    m_activeBounds.max.x = m_xc + m_width;
    m_activeBounds.max.y = m_yc + m_height;

    for (auto& item : m_items) {
        if (item->candidateForCreation()) {
            auto b = item->getInitBounds();
            if (b.Intersects2D(m_activeBounds)) {
                auto entity = item->create();
                m_parentEntity->AddChild(entity);
                m_itemCount++;
                //if (Engine::get().isRunning()) {
                //    obj->restart();
                //   obj->Begin();
                //}
            }
        } else if (item->candidateForDestruct()) {
            auto b = item->getCurrentBounds();
            if (!b.Intersects2D(m_activeBounds)) {
                item->destroy();
                m_itemCount--;
            }
        }
    }
}


void DynamicWorldBuilder::OnCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    //std::cout << "cam pos = " << pos.x << "\n";
    if (pos.x >= m_xmax || pos.x <= m_xmin || pos.y >= m_ymax || pos.y <= m_ymin) {
        // update the world ONLY if cammera is outside of the inner window
        UpdateWorld(pos);
    }
}


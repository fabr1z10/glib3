#include <monkey/dynamicworld.h>
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <iostream>

//void DynamicWorldBuilder::SetCamera(Camera * camera) {
//    camera->OnMove.Register(this, [&] (Camera* cam) { this->OnCameraMove(cam); });
//    glm::vec3 camPos = camera->GetPosition();
//    m_x0 = camPos.x;
//    m_y0 = camPos.y;
//    std::cout << "Dynamic world builder, set camera with initial position (" << m_x0 << ", " << m_y0 << ")\n";
//    UpdateWorld(camPos);
//}

void DynamicWorldBuilder::Init() {
    std::cerr << "INIT DYNAMIC WORLD!\n";
    auto cam = Ref::Get<Camera>(m_camName);
    cam->OnMove.Register(this, [&] (Camera* cam) { this->OnCameraMove(cam); });
    glm::vec3 camPos = cam->GetPosition();
    // inititalize the center
    m_xc0 = camPos.x;
    m_yc0 = camPos.y;
    m_x = -1;
    m_y = -1;
    m_parentEntity =Ref::Get<Entity>("main").get();
    m_parentEntity->onRemove.Register(this, [&] (Entity* e) {
        auto it = m_outBounds.find(e->GetId());
        if (it != m_outBounds.end()) {
            // item has been removed by dynamic world
            m_outBounds.erase(it);
            return;
        }
        std::cerr << "REMOVED EXTERNALLY ENTITY " << e->GetId() << "\n";
        m_removedItems.insert(e->GetId());

    });
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
        // if item has been removed, nothing to do
        //std::cerr << item.id << "\n";
        bool forciblyRemoved = m_removedItems.count(item.id) > 0;
        Bounds b = item.m_localBounds;
        if (!forciblyRemoved) {
            if (!item.active) {
                b.Translate(item.m_initPos);
                if (b.Intersects2D(m_activeBounds)) {
                    auto obj = item.m_blueprint;
                    item.active = true;
                    std::cerr << "adding item " << item.m_blueprint->GetId() << std::endl;
                    m_parentEntity->AddChild(obj);
                    obj->SetPosition(item.m_initPos);
                    if (Engine::get().isRunning()) {
                        obj->restart();
                        obj->Begin();
                    }
                }
            } else {
                // already created
                b.Translate(item.m_blueprint->GetPosition());
                if (!b.Intersects2D(m_activeBounds)) {
                    Engine::get().Remove(Ref::Get<Entity>(item.m_blueprint->GetId()));
                    std::cerr << "dropping item " << item.m_blueprint->GetId() << std::endl;
                    item.active = false;
                    m_outBounds.insert(item.id);
                }
            }
        } else {
            b.Translate(item.m_initPos);
            if (!item.createOnce && b.Intersects2D(m_activeBounds)) {
                m_removedItems.erase(item.id);
                auto obj = item.m_blueprint;
                item.active = true;
                std::cerr << "adding item " << item.m_blueprint->GetId() << std::endl;
                m_parentEntity->AddChild(obj);
                obj->SetPosition(item.m_initPos);
                if (Engine::get().isRunning()) {
                    obj->restart();
                    obj->Begin();
                }
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

//void DynamicWorldBuilder::AddItem(std::shared_ptr<Entity> parent, std::shared_ptr<Entity> entity) {
void DynamicWorldBuilder::AddItem(std::shared_ptr<Entity> entity) {

    // compute bounds;
    auto renderer = entity->GetComponent<Renderer>();
    glm::vec3 pos = entity->GetPosition();
    Bounds bounds;
    if (renderer != nullptr) {
        bounds = renderer->GetBounds();
        //bounds.min += pos;
        //bounds.max += pos;
    } else {
        bounds.min = glm::vec3(-0.5f, -0.5f, 0.0f);
        bounds.max = glm::vec3(0.5f, 0.5f, 0.0f);
    }
    DynamicWorldItem item;
    item.m_blueprint = entity;
    item.id = entity->GetId();
    item.m_localBounds.min = bounds.min;
    item.m_localBounds.max = bounds.max;
    item.m_initPos = pos;
    item.createOnce = true;
//    item.m_bounds = item.m_localBounds;
//    item.m_bounds.Tr
//    item.m_bounds.min = item.m_localBounds.min + glm::vec3(pos.x, pos.y, 0.0f);
//    item.m_bounds.max = item.m_localBounds.max + glm::vec3(pos.x, pos.y, 0.0f);
//    //item.m_object = nullptr;
//    std::cout << "Adding item with bounds = (" << item.m_bounds.min.x << ", " << item.m_bounds.min.y << ") to ("
//    << item.m_bounds.max.x << ", " << item.m_bounds.max.y << ")\n";
    m_items.push_back(item);
}

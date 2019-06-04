#include "gfx/dynamicworld.h"
#include "gfx/engine.h"
#include "gfx/components/renderer.h"
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
    auto cam = Ref::Get<OrthographicCamera>(m_camName);
    cam->OnMove.Register(this, [&] (Camera* cam) { this->OnCameraMove(cam); });
    glm::vec3 camPos = cam->GetPosition();
    m_x0 = camPos.x;
    m_y0 = camPos.y;
    m_x = -1;
    m_y = -1;
    UpdateWorld(camPos);

}

void DynamicWorldBuilder::UpdateWorld(glm::vec3 pos) {
    int xp = static_cast<int>((pos.x - m_x0) / m_width);
    int yp = static_cast<int>((pos.y - m_y0) / m_height);

    if (xp != m_x || yp != m_y) {
        m_x = xp;
        m_y = yp;
    } else {
        return;
    }

    m_activeBounds.min.x = m_x0 + (m_x-2)*m_width ;
    m_activeBounds.min.y = m_y0 + (m_y-2)*m_height ;
    m_activeBounds.max.x = m_x0 + (m_x+2)*m_width ;
    m_activeBounds.max.y = m_y0 + (m_y+2)*m_height ;

    std::cout << "active bounds = " << m_x << ", " << m_y << "\n";
    // update visible items
    for (auto& item : m_items) {

        if (item.id == -1 && !item.removed) {
            // glm::vec3 pos = item.m_blueprint->GetPosition();
            Bounds b = item.m_bounds;
            //b.min += glm::vec2(pos.x, pos.y);
            //b.max += glm::vec2(pos.x, pos.y);
            if (b.Intersects(m_activeBounds)) {
                std::cout << "Creating item with bounds (" << b.min.x << ", " << b.min.y << "), (" << b.max.x << ", " << b.max.y << ")\n";
                auto obj = item.m_blueprint->clone();

                item.id = obj->GetId();
                item.ref = obj;
                item.m_parent->AddChild(obj);
            }
        } else {
            // already created
            if (Ref::isAlive(item.id)) {
                glm::vec3 pos = item.ref->GetPosition();
                Bounds b = item.m_bounds;
                //b.min += glm::vec2(pos.x, pos.y);
                //b.max += glm::vec2(pos.x, pos.y);

                if (!b.Intersects(m_activeBounds)) {
                    std::cout << "Removing item at (" << pos.x << ", " << pos.y << "...\n";
                    Engine::get().Remove(item.ref);
                    item.ref = nullptr;
                    item.id = -1;
                }

            } else {
                // the item has been destroyed externally.
                item.removed = true;
                item.id= -1;
                item.ref = nullptr;
            }

        }

    }

}

void DynamicWorldBuilder::OnCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    UpdateWorld(pos);
}

void DynamicWorldBuilder::AddItem(std::shared_ptr<Entity> parent, std::shared_ptr<Entity> entity) {

    // compute bounds;
    auto renderer = entity->GetComponent<Renderer>();
    glm::vec3 pos = entity->GetPosition();
    Bounds3D bounds;
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
    item.m_parent = parent;
    //item.createOnce = createOnce;
    item.m_localBounds.min = glm::vec2(bounds.min);
    item.m_localBounds.max = glm::vec2(bounds.max);
    item.m_bounds.min = item.m_localBounds.min + glm::vec2(pos.x, pos.y);
    item.m_bounds.max = item.m_localBounds.max + glm::vec2(pos.x, pos.y);
    //item.m_object = nullptr;
    std::cout << "Adding item with bounds = (" << item.m_bounds.min.x << ", " << item.m_bounds.min.y << ") to ("
    << item.m_bounds.max.x << ", " << item.m_bounds.max.y << ")\n";
    m_items.push_back(item);
}

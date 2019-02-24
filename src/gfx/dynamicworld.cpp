#include "gfx/dynamicworld.h"
#include "gfx/components/renderer.h"
#include <iostream>

void DynamicWorldBuilder::SetCamera(Camera * camera) {
    camera->OnMove.Register(this, [&] (Camera* cam) { this->OnCameraMove(cam); });
    glm::vec3 camPos = camera->GetPosition();
    m_x0 = camPos.x;
    m_y0 = camPos.y;
    std::cout << "Dynamic world builder, set camera with initial position (" << m_x0 << ", " << m_y0 << ")\n";
    UpdateWorld(camPos);
}

void DynamicWorldBuilder::UpdateWorld(glm::vec3 pos) {
    int xp = static_cast<int>((pos.x - m_x0) / m_width);
    int yp = static_cast<int>((pos.y - m_y0) / m_height);
    if (xp != m_x || yp != m_y) {
        m_x = xp;
        m_y = yp;
    }
    m_activeBounds.min.x = m_x0 + (m_x-2)*m_width ;
    m_activeBounds.min.y = m_y0 + (m_y-2)*m_height ;
    m_activeBounds.max.x = m_x0 + (m_x+2)*m_width ;
    m_activeBounds.max.y = m_y0 + (m_y+2)*m_height ;


    for (auto& item : m_items) {

        if (item.m_object == nullptr) {
            glm::vec3 pos = item.m_blueprint->GetPosition();
            Bounds b = item.m_bounds;
            b.min += glm::vec2(pos.x, pos.y);
            b.max += glm::vec2(pos.x, pos.y);
            if (b.Intersects(m_activeBounds)) {
                std::cout << "Creating item with bounds (" << b.min.x << ", " << b.min.y << "), (" << b.max.x << ", " << b.max.y << ")\n";
                item.m_object = item.m_blueprint->clone();
                item.m_parent->AddChild(item.m_object);
            }
        } else {
            // check if it's out of the active area
            glm::vec3 pos = item.m_object->GetPosition();
            Bounds b = item.m_bounds;
            b.min += glm::vec2(pos.x, pos.y);
            b.max += glm::vec2(pos.x, pos.y);
            if (!b.Intersects(m_activeBounds)) {
                std::cout << "Removing ...\n";
            }
        }

    }

}

void DynamicWorldBuilder::OnCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    UpdateWorld(pos);
}

void DynamicWorldBuilder::AddItem(Entity* parent, std::shared_ptr<Entity> entity) {

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
    item.m_localBounds.min = glm::vec2(bounds.min);
    item.m_localBounds.max = glm::vec2(bounds.max);
    item.m_bounds.min = item.m_localBounds.min + glm::vec2(pos.x, pos.y);
    item.m_bounds.max = item.m_localBounds.max + glm::vec2(pos.x, pos.y);
    item.m_object = nullptr;
    std::cout << "Adding item with bounds = (" << item.m_bounds.min.x << ", " << item.m_bounds.min.y << ") to ("
    << item.m_bounds.max.x << ", " << item.m_bounds.max.y << ")\n";
    m_items.push_back(item);
}

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
    auto cam = Ref::Get<Camera>(m_camName);
    cam->OnMove.Register(this, [&] (Camera* cam) { this->OnCameraMove(cam); });
    glm::vec3 camPos = cam->GetPosition();
    // inititalize the center
    m_xc0 = camPos.x;
    m_yc0 = camPos.y;
    m_x = -1;
    m_y = -1;
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

    //std::cout << "UPDATING WORLD! center = (" << m_xc << ", " << m_yc << ")\n";
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
                item.ref = obj.get();
                auto main = Ref::Get<Entity>("main");
                main->AddChild(obj);
                if (Engine::get().isRunning()) {
                    obj->start();
                    obj->Begin();
                }
                //item.m_parent->AddChild(obj);
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

                    Engine::get().Remove(Ref::Get<Entity>(item.id));
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
    item.m_localBounds.min = bounds.min;
    item.m_localBounds.max = bounds.max;
    item.m_bounds.min = item.m_localBounds.min + glm::vec3(pos.x, pos.y, 0.0f);
    item.m_bounds.max = item.m_localBounds.max + glm::vec3(pos.x, pos.y, 0.0f);
    //item.m_object = nullptr;
    std::cout << "Adding item with bounds = (" << item.m_bounds.min.x << ", " << item.m_bounds.min.y << ") to ("
    << item.m_bounds.max.x << ", " << item.m_bounds.max.y << ")\n";
    m_items.push_back(item);
}

#include <monkey/hotspot.h>
#include <gfx/engine.h>
#include <iostream>
#include <gfx/scheduler.h>
#include <gfx/move.h>
#include <gfx/renderer.h>
#include <gfx/animate.h>
#include <gfx/sequence.h>

void HotSpot::CursorPosCallback(GLFWwindow*, double x, double y) {
    bool isActive =m_cam->IsInViewport(x, y);
    if (m_active != isActive) {
        if (isActive)
            std::cout << "Entering area\n";
        else
            std::cout << "Exiting area\n";
    }
    m_active = isActive;
}


void HotSpot::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (m_active && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        glm::vec2 wp = m_cam->GetWorldCoordinates(glm::vec2(x, y));
        auto scheduler = Engine::get().GetRef<Scheduler>("_scheduler");
        auto player = Engine::get().GetRef<Entity>("player");
        auto script = std::make_shared<Script>(0);
        glm::vec2 currentPos(player->GetPosition());
        glm::vec2 delta = wp - currentPos;
        if (delta != glm::vec2(0.0f)) {
            std::string anim;
            std::string anim2;
            if (std::fabs(delta.x) > std::fabs(delta.y)) {
                anim = "walk_right";
                anim2 = "idle_right";
            }
            else {
                if (delta.y > 0) {
                    anim = "walk_back";
                    anim2 = "idle_back";
                } else {
                    anim = "walk_front";
                    anim2 = "idle_front";
                }
            }
            bool flipX = (anim == "walk_right" && delta.x < 0);
            player->GetComponent<Renderer>()->SetFlipX(flipX);
            auto p = std::make_shared<Sequence>(0);
            p->Push(std::make_shared<Animate>(0, player, anim));
            p->Push(std::make_shared<MoveTo>(1, player, wp, 50.0f));
            p->Push(std::make_shared<Animate>(2, player, anim2));
            script->AddActivity(p);
            //script->AddActivity(std::make_shared<Animate>(0, player, anim));
            //script->AddActivity(std::make_shared<MoveTo>(1, player, wp, 50.0f));
            //script->AddActivity(std::make_shared<Animate>(2, player, anim2));
            //script->AddEdge(0, 1);
            //script->AddEdge(1, 2);
            scheduler->AddScript("_walk", script);
        }
        // if (m_shape->isPointInside(wp))
        //  m_target->SetPosition(wp);


    }

}

void HotSpot::ScrollCallback(GLFWwindow*, double x , double y) {


}

void HotSpot::Start() {
    // Get the underlying camera
    m_cam = Engine::get().GetRef<OrthographicCamera>(m_camId);
    m_target = Engine::get().GetRef<Entity>(m_targetId);
}


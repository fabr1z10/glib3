#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spriteview/mousecontrol.h>
#include <gfx/entity.h>
#include <iostream>
#include <gfx/math/geom.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>

extern GLFWwindow* window;

void ViewerController::Start() {
    //m_cam = dynamic_cast<OrthographicCamera*>(m_entity->GetCamera());
}

void ViewerController::onMove(glm::vec2 pos) {
    glm::vec3 camPos=  m_cam->GetPosition();
    if (m_lmbPressed) {
        glm::vec2 size = m_cam->getOrthoSize();
        double deltaX =(pos.x - m_xPrev);
        double deltaY =(pos.y - m_yPrev);
        glm::vec3 d = m_cam->GetPosition()+ glm::vec3(static_cast<float>(deltaX), static_cast<float>(deltaY), 0.0f);
        d.x = Clamp(d.x, -400+size.x*0.5f,400-size.x*0.5f);
        d.y = Clamp(d.y, -300+size.y*0.5f,300-size.y*0.5f);

        m_cam->SetPosition(d,glm::vec3(0,0,-1));
        m_xPrev = pos.x;
        m_yPrev = pos.y;
    }

}

void ViewerController::onClick(glm::vec2 pos, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        m_lmbPressed = (action == GLFW_PRESS);

        m_xPrev = pos.x;
        m_yPrev = pos.y;
        std::cout << "button down in (" << m_xPrev << ", " << m_yPrev << ")\n";
    }
}
//
//void ViewerController::CursorPosCallback(GLFWwindow*, double x, double y) {
//    if (m_lmbPressed) {
//
//        double deltaX = -(x - m_xPrev);
//        double deltaY = (y - m_yPrev);
//        glm::vec3 pos = m_cam->GetPosition()+ glm::vec3(static_cast<float>(deltaX), static_cast<float>(deltaY), 0.0f);
//        m_cam->SetPosition(pos,glm::vec3(0,0,-1));
//        m_xPrev = x;
//        m_yPrev = y;
//    }
//
//}
//
//
void ViewerController::onEnter() {
}
void ViewerController::onLeave() {
    m_lmbPressed = false;
}
std::type_index ViewerController::GetType() {
    return std::type_index(typeid(HotSpot));
}

//void ViewerController::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
//    if (button == GLFW_MOUSE_BUTTON_LEFT) {
//
//        m_lmbPressed = (action == GLFW_PRESS);
//        if (action == GLFW_PRESS) {
//            glfwGetCursorPos(window, &m_xPrev, &m_yPrev);
//        }
//    }
//}
//
//void ViewerController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    // reset cam position
//    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
//        m_cam->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0,0,-1));
//        m_cam->setOrthoSize(m_defaultCamWidth, m_defaultCamHeight);
//    }
//    // toggle grid
//    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
//        auto grid =Engine::get().GetRef<Entity>("grid");
//        grid->SetActive(!grid->IsActive());
//    }
//    // toggle update
//    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
//        auto grid =Engine::get().GetRef<Entity>("model");
//        grid->SetEnableUpdate(!grid->IsUpdateEnabled());
//        m_update = grid->IsUpdateEnabled();
//    }
//    // advance frame
//    if (key == GLFW_KEY_UP && action == GLFW_PRESS && !m_update) {
//        auto grid =Engine::get().GetRef<Entity>("model");
//        auto c = grid->GetChildren();
//        for (auto& child : c) {
//            auto renderer = child->GetComponent<Renderer>();
//            int frame = renderer->GetFrame() + 1;
//            renderer->SetFrame(frame);
//        }
//    }
//    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && !m_update) {
//        auto grid =Engine::get().GetRef<Entity>("model");
//        auto c = grid->GetChildren();
//        for (auto& child : c) {
//            auto renderer = child->GetComponent<Renderer>();
//            int frame = renderer->GetFrame() -1;
//            renderer->SetFrame(frame);
//        }
//    }
//
//
//
//
////    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
//
//
//
////    {
////        m_factory->AdvanceTime(-60);
////    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
////        m_factory->AdvanceTime(60);
////    }
//
//}
//
//
void ViewerController::onScroll(float x, float y) {

    double xx,yy;
    glfwGetCursorPos(window, &xx, &yy);

    glm::vec2 pp = m_cam->GetWorldCoordinates(glm::vec2(xx, yy));
    glm::vec3 cp = m_cam->GetPosition();
    glm::vec2 camPos(cp);
    glm::vec2 newPos = camPos +0.1f*(pp-camPos);
    glm::vec2 size = m_cam->getOrthoSize();
    if (y< 0)
        size *= 1.1f;
    else
        size /= 1.1f;
    int w = std::min(800, static_cast<int>(size.x+0.5f));
    int h = std::min(600, static_cast<int>(size.y+0.5f));
    int d = std::min(w, h);
    m_cam->setOrthoSize(d, d);
    float x1 = static_cast<int>(newPos.x) + (d % 2 == 1 ? 0.5f : 0.0f);
    float y1 = static_cast<int>(newPos.y)+ (d % 2 == 1 ? 0.5f : 0.0f);
    x1 = Clamp(x1, -400+d*0.5f,400-d*0.5f);
    y1 = Clamp(y1, -300+d*0.5f,300-d*0.5f);
    std::cout << "setting w= "<< w << ", h= " << h<<" x = " << x1 << ", y = " << y1 << "\n";
    m_cam->SetPosition(glm::vec3(x1, y1, cp.z), glm::vec3(0,0,-1));

}
////

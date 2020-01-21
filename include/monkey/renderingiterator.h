#pragma once

#include <monkey/iterator.h>
#include <monkey/entity.h>

struct CameraInfo {
    Entity* entity;
    Camera* camera;
    //glm::vec4 viewport;
};

class RenderingIterator : public DepthFirstIterator<Entity> {
public:
    RenderingIterator() : DepthFirstIterator<Entity>() {}
    RenderingIterator(Entity* root) : DepthFirstIterator<Entity>(root) {}
    void onPop(Entity*) override;
    void onNext() override;
    Camera* GetCamera();
private:
    std::stack<CameraInfo> m_cameraStack;
};

class HotSpotIterator : public DepthFirstIterator<Entity> {
public:
    HotSpotIterator() : DepthFirstIterator<Entity>() {}
    HotSpotIterator(Entity* root) : DepthFirstIterator<Entity>(root) {}
    void onPop(Entity*) override;
    void onNext() override;
    Camera* GetCamera();
private:
    std::stack<CameraInfo> m_cameraStack;
};

struct ResizeCameraInfo {
    Entity* entity;
    Camera* camera;
    glm::vec4 deviceViewport;
    glm::vec4 viewport;
};

class ResizeIterator : public DepthFirstIterator<Entity> {
public:
    ResizeIterator() : DepthFirstIterator<Entity>() {}
    ResizeIterator(Entity* root, glm::vec2 winSize, glm::vec2 actSize) : DepthFirstIterator<Entity>(root), m_winSize{winSize}, m_actualSize{actSize} {}
    void onPop(Entity*) override;
    void onNext() override;
    Camera* GetCamera();
private:
    glm::vec4 deviceToScreenViewport(glm::vec4);
    glm::vec2 m_winSize;
    glm::vec2 m_actualSize;
    std::stack<ResizeCameraInfo> m_cameraStack;
};
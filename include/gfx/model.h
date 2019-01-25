#pragma once

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class Entity;

struct ModelComponent {
    std::string name;
    std::string mesh;
    glm::vec3 pos;
    std::string parent;
};

// a model is a blueprint for complex objects made up of a tree of entities having

class Model {
public:
    Model () {}
    void AddComponent(const ModelComponent& c);
    std::shared_ptr<Entity> Create();
    std::string GetName() const;
private:
    std::string m_name;
    std::vector<ModelComponent> m_components;
};

inline std::string Model::GetName() const {
    return m_name;
}

inline void Model::AddComponent(const ModelComponent& c) {
    m_components.push_back(c);
}
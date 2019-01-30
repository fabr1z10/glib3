#pragma once

#include <gfx/simplemodel.h>

struct ModelComponent {
    std::string name;
    SimpleModel* model;
    std::string parent;
};

struct AnimationDefinition {
    std::string node;
    std::string anim;
    glm::vec3 pos;
};

class CompositeModel : public IModel {
public:
    CompositeModel () {}
    std::unique_ptr<IModelStatus> GetModelStatus() override;
    void AddComponent(const std::string&, SimpleModel* model, const std::string& parent);
    const std::unordered_map<std::string, ModelComponent>& GetComponents() const;
    const std::vector<AnimationDefinition>& GetAnimationDefinition(const std::string&) const;
    std::vector<std::string> GetAnimations() override;
    void AddAnimation(const std::string& name, std::vector<AnimationDefinition>& def);
    ModelType GetType() const override;
    Bounds3D GetBounds() const override {
        return Bounds3D();
    }
private:
    std::unordered_map<std::string, ModelComponent> m_components;
    // a composite model needs to describe animations as (node, anim) pairs
    std::unordered_map<std::string, std::vector<AnimationDefinition>> m_animInfo;
};

inline ModelType CompositeModel::GetType() const {
    return ModelType::COMPOSITESPRITE;
}

inline void CompositeModel::AddAnimation(const std::string& name, std::vector<AnimationDefinition>& def) {
    m_animInfo.insert(std::make_pair(name, def));
}

inline const std::unordered_map<std::string, ModelComponent>& CompositeModel::GetComponents() const {
    return m_components;
}

inline void CompositeModel::AddComponent(const std::string& name, SimpleModel* model, const std::string& parent) {
    m_components.insert (std::make_pair(name, ModelComponent{name, model, parent}));
}

class CompositeModelStatus : public IModelStatus {
public:
    CompositeModelStatus(CompositeModel* model) : m_model(model) {}
    void Init(Entity*) override ;
    void Update(double dt) override ;
    void AddComponent (const std::string& s, const SimpleModelStatus& status) {
        m_componentStates.insert(std::make_pair(s,status));
    }
    void AdvanceFrame(int) override;

    void SetAnimation (const std::string& anim) override;
private:
    std::unordered_map<std::string, SimpleModelStatus> m_componentStates;
    CompositeModel* m_model;
};



//#pragma once
//
//#include <gfx/simplemodel.h>
//
//struct ModelComponent {
//    std::string name;
//    SimpleModel* model;
//    std::string parent;
//};
//
//struct AnimationDefinition {
//    std::string node;
//    std::string anim;
//    glm::vec3 pos;
//};
//
//class CompositeModel : public IModel {
//public:
//    CompositeModel () {}
//
//    std::unique_ptr<IModelStatus> GetModelStatus() override;
//    void AddComponent(const std::string&, SimpleModel* model, const std::string& parent);
//    const std::unordered_map<std::string, ModelComponent>& GetComponents() const;
//    const std::vector<AnimationDefinition>& GetAnimationDefinition(const std::string&) const;
//    std::vector<std::string> GetAnimations() override;
//    void AddAnimation(const std::string& name, std::vector<AnimationDefinition>& def);
//    ModelType GetType() const override;
//    Bounds3D GetBounds() const override {
//        return Bounds3D();
//    }
//    void SetDefaultAnimation(const std::string&);
//    std::string GetDefaultAnimation() const;
//private:
//    std::string m_defaultAnimation;
//    std::unordered_map<std::string, ModelComponent> m_components;
//    // a composite model needs to describe animations as (node, anim) pairs
//    std::unordered_map<std::string, std::vector<AnimationDefinition>> m_animInfo;
//};
//
//inline std::string CompositeModel::GetDefaultAnimation() const {
//    return m_defaultAnimation;
//}
//
//inline void CompositeModel::SetDefaultAnimation(const std::string& anim) {
//    m_defaultAnimation = anim;
//}
//
//inline ModelType CompositeModel::GetType() const {
//    return ModelType::COMPOSITESPRITE;
//}
//
//inline void CompositeModel::AddAnimation(const std::string& name, std::vector<AnimationDefinition>& def) {
//    if (m_animInfo.empty()) {
//        SetDefaultAnimation(name);
//    }
//    m_animInfo.insert(std::make_pair(name, def));
//}
//
//inline const std::unordered_map<std::string, ModelComponent>& CompositeModel::GetComponents() const {
//    return m_components;
//}
//
//inline void CompositeModel::AddComponent(const std::string& name, SimpleModel* model, const std::string& parent) {
//    m_components.insert (std::make_pair(name, ModelComponent{name, model, parent}));
//}
//
//class CompositeModelStatus : public IModelStatus {
//public:
//    CompositeModelStatus(CompositeModel* model) : m_model(model), m_entity(nullptr) {}
//    void Init(Entity*) override ;
//    void Update(double dt) override ;
//    void AddComponent (const std::string& s, std::unique_ptr<IModelStatus> status) {
//        m_componentStates.insert(std::make_pair(s,std::move(status)));
//    }
//    void AdvanceFrame(int) override;
//    Entity* GetEntity() override;
//    void SetAnimation (const std::string& anim, bool fwd) override;
//    bool IsAnimComplete() const override;
//private:
//    std::unordered_map<std::string, std::unique_ptr<IModelStatus>> m_componentStates;
//    CompositeModel* m_model;
//    Entity* m_entity;
//};
//
//inline Entity* CompositeModelStatus::GetEntity() {
//    return m_entity;
//}
//
//

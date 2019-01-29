//#pragma once
//
//#include <gfx/components/animator.h>
//
//// animator f
//class SpriteAnimator : public Animator {
//public:
//    explicit SpriteAnimator(std::shared_ptr<Model> model);
//    void Start() override;
//    void Update (double) override;
//    void SetAnimation (const std::string&) override;
//    void SetAnimation (const std::string& node, const std::string& animation) override;
//    void addRenderer (const std::string& name, Renderer*);
//    bool loopEnd() const override {return false;}
//    std::type_index GetType() override;
//    std::shared_ptr<AnimatorState> SaveState() override;
//    void LoadState(std::shared_ptr<AnimatorState>) override;
//    bool HasAnimation(const std::string&) override ;
//    bool HasAnimation(const std::string&, const std::string&) override;
//private:
//    std::shared_ptr<Model> m_model;
//    std::unordered_map<std::string, Status> m_status;
//};
//
//class SpriteAnimatorState : public AnimatorState {
//public:
//    std::unordered_map<std::string, SimpleAnimatorState> m_states;
//};
//
//inline std::type_index SpriteAnimator::GetType() {
//    return std::type_index(typeid(Animator));
//}
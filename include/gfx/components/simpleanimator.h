//#pragma once
//
//#include <gfx/components/animator.h>
//
//class SimpleAnimator : public Animator {
//public:
//    explicit SimpleAnimator (std::shared_ptr<IMesh> mesh);
//    void Start() override;
//    void Update (double) override;
//    void SetAnimation (const std::string& anim) override ;
//    void SetAnimation (const std::string& node, const std::string& anim) override ;
//    bool loopEnd() const override;
//    std::type_index GetType() override;
//    std::shared_ptr<AnimatorState> SaveState() override;
//    void LoadState(std::shared_ptr<AnimatorState>) override;
//private:
//    std::shared_ptr<SpriteMesh> m_mesh;
//    Status m_status;
//
//};
//
//
//
//inline bool SimpleAnimator::loopEnd() const {
//    return m_status.loopEnd;
//}
//
//inline std::type_index SimpleAnimator::GetType() {
//    return std::type_index(typeid(Animator));
//}
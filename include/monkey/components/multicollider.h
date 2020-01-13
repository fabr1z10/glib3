//#pragma once
//
//#include <monkey/components/collider.h>
//#include <monkey/error.h>
//
//class MultiCollider : public Collider {
//public:
//    MultiCollider (const std::unordered_map<std::string, std::shared_ptr<Shape>>& shapes, int tag, int flag, int mask, const std::string& initialShape);
//    void SwitchTo (const std::string&);
//    void Start () override;
//    std::type_index GetType() override;
//private:
//    std::unordered_map<std::string, std::shared_ptr<Shape>> m_shapes;
//    std::unordered_map<std::string, Entity*> m_gfx;
//    std::string m_current;
//};
//
//
//
//
//
//inline std::type_index MultiCollider::GetType() {
//    return std::type_index(typeid(Collider));
//}

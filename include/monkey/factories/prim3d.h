#include <monkey/factory.h>
#include <monkey/spritemesh.h>


class ModelBox3D : public FactoryMethod<IModel> {
public:
    std::shared_ptr<IModel> Create(luabridge::LuaRef& ref) override;
private:

    std::shared_ptr<IMesh> CreateTopMesh (float w, float h, float d, const std::string&, float rx, float rz);
    std::shared_ptr<IMesh> CreateSideMesh (float w, float h, float d, const std::string&, float rx, float ry);
};

class ModelTrapezoid3D : public FactoryMethod<IModel> {
public:
    std::shared_ptr<IModel> Create(luabridge::LuaRef& ref) override;
private:
    std::shared_ptr<IMesh> CreateTopMesh (const std::vector<float>& points, float d, const std::string&, float rx, float rz);
    std::shared_ptr<IMesh> CreateSideMesh (const std::vector<float>& points, float d, float h, const std::string&, float rx, float rz, bool parallel);
    std::vector<glm::vec3> m_topPoints;
};
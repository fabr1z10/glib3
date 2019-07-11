#include <gfx/factory.h>
#include <gfx/spritemesh.h>


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

};
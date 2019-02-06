#pragma once

#include <gfx/imodel.h>
#include <gfx/spritemesh.h>
#include <gfx/components/renderer.h>

class SimpleModelStatus : public IModelStatus {
public:
    explicit SimpleModelStatus(const SpriteMesh &mesh) : m_mesh(mesh), inc(1) {

    }
    void Init(Entity*) override;

    void Update(double dt) override ;
    void AdvanceFrame(int) override;
    void SetAnimation (const std::string& anim, bool fwd) override;
    Entity* GetEntity() override {
        return renderer->GetObject();
    }
    bool IsAnimComplete() const override;

private:
    int inc;
    std::string animation;
    int frame;
    double time;
    const AnimInfo* m_animInfo;
    const SpriteMesh& m_mesh;
    Renderer* renderer;
    bool m_animCompleted;
};

inline bool SimpleModelStatus::IsAnimComplete() const {
    return m_animCompleted;
}


class SimpleModel : public IModel {
public:
    explicit SimpleModel (std::shared_ptr<SpriteMesh> mesh) : m_mesh(mesh) {}
    std::unique_ptr<IModelStatus> GetModelStatus() override;
    std::shared_ptr<SpriteMesh> GetMesh();
    ModelType GetType() const override;
    Bounds3D GetBounds() const override;
    std::vector<std::string> GetAnimations() override;
private:
    std::shared_ptr<SpriteMesh> m_mesh;
};

inline Bounds3D SimpleModel::GetBounds() const {
    return m_mesh->GetBounds();
}

inline ModelType SimpleModel::GetType() const {
    return ModelType::SIMPLESPRITE;
}

inline std::shared_ptr<SpriteMesh> SimpleModel::GetMesh() {
    return m_mesh;
}
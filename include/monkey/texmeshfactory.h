#pragma once

#include <monkey/mesh.h>
#include <monkey/math/shapes/plane3d.h>
#include "visitor.h"
#include <memory>

struct TexInfo {
	std::string id;
	std::string tex;
	glm::vec2 repeat;
	// glm::vec2 offset;
	// glm::vec2 skew;
};

// creates a mesh from a shape
class TexMeshFactory :
    public AcyclicVisitor,
	public Visitor<Plane3D>
{
public:
	TexMeshFactory ();
	void addTexInfo (const TexInfo&);
	std::vector<std::shared_ptr<IMesh>> CreateMesh (Shape& s);


private:
	std::unordered_map<std::string, TexInfo> m_textureInfo;
	std::vector<std::shared_ptr<IMesh>> m_meshes;
	void visit(Plane3D&) override;
};

inline void TexMeshFactory::addTexInfo (const TexInfo& info) {
	m_textureInfo[info.id] = info;

}

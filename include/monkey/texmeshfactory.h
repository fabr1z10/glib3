#pragma once

#include <monkey/mesh.h>
#include <monkey/math/shapes/plane3d.h>
#include "visitor.h"
#include <memory>
#include <monkey/math/shapes/polychain3d.h>
#include <monkey/math/shapes/surf2d.h>

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
	public Visitor<Plane3D>,
	public Visitor<PolyChain3D>,
	public Visitor<Polygon>,
	public Visitor<ISurf2D>
{
public:
	TexMeshFactory ();
	void addTexInfo (const TexInfo&);
	std::vector<std::shared_ptr<IMesh>> CreateMesh (Shape& s);


private:
	std::unordered_map<std::string, TexInfo> m_textureInfo;
	std::vector<std::shared_ptr<IMesh>> m_meshes;
	void visit(Plane3D&) override;
	void visit(PolyChain3D&) override;
    void visit(Polygon&) override;
    void visit(ISurf2D&) override;

};

inline void TexMeshFactory::addTexInfo (const TexInfo& info) {
	m_textureInfo[info.id] = info;

}

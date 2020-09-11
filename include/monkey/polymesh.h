#pragma once

#include "monkey/ref.h"
#include "monkey/texturedmesh.h"

class PolyMesh : public Ref {
public:
	// returns the number of meshes generated
	size_t getMeshCount () const;
	const std::vector<std::shared_ptr<IMesh > >& getMeshes() const;
private:
	std::vector<std::shared_ptr<IMesh > > m_meshes;
};

inline size_t PolyMesh::getMeshCount() const {
	return m_meshes.size();
}

const std::vector<std::shared_ptr<IMesh>> & PolyMesh::getMeshes() const {
	return m_meshes;
}

class Plane3D : public PolyMesh {
public:
	Plane3D(const ITable&);


};
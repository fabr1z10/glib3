#pragma once

#include <monkey/model/basicmodel.h>
#include <memory>
#include "monkey/texturedmesh.h"
// primitives 3d (color and tex)

class Box3D : public BasicModel {
public:
    Box3D (const ITable&);
	void Draw (Shader*);

private:

	std::vector<std::shared_ptr<TexturedMesh<Vertex3DN> > > m_meshes;

};

class Sphere3D : public BasicModel {
public:
    Sphere3D (const ITable&);
};

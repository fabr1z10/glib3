#pragma once

#include <monkey/components/hotspot.h>
#include <monkey/math/funcs.h>
#include <monkey/math/geom.h>
#include <monkey/components/scripthotspot.h>
#include <monkey/math/algo/shortestpath.h>
#include <monkey/vertices.h>
#include <monkey/dynamicmesh.h>
#include <monkey/components/inputmethod.h>

class Scheduler;

class Road : public Component {
public:
    //WalkArea (std::shared_ptr<IShape> shape, int priority);
    Road(const ITab&);
    void Update(double) override;
    void Start() override;
    using ParentClass = Road;
    std::type_index GetType() override;
private:
	std::shared_ptr<DynamicMesh<VertexColor>> m_mesh;
	float m_curvature;
	float m_step;
	InputMethod * m_input;
	Camera* m_cam;
	// position of the player in the road (distance from beginning)
	float m_s;
	// distance between horizontal bands
	float m_d0;
	float m_speed;
	float m_acceleration;
	// number of points per band
	int m_n;
};



inline std::type_index Road::GetType() {
    return std::type_index(typeid(Road));
}


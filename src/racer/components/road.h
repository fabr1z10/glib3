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


struct RoadSection {
	RoadSection() = default;
	RoadSection(long steps, float width, float curvature, float slope, float offset) :
		width(width), curvature(curvature), slope(slope), offset(offset), steps(steps) {}
	long startIndex;
	long steps;
	float width;
	float curvature;
	float slope;
	float offset;
};


struct QuadInfo {
    glm::vec4 loc;
    glm::vec2 offset;
};

struct RoadItem {
    float x;
    float height;
    int quadId;
    bool flipH;
    int i;
};




class Road : public Component {
public:
    //WalkArea (std::shared_ptr<IShape> shape, int priority);
    Road(const ITab&);
    void Update(double) override;
    void Start() override;
    using ParentClass = Road;
    std::type_index GetType() override;
private:
	int addRoadVertices(std::vector<VertexColor>&, std::vector<unsigned>&, float x, float y, float z, unsigned colorIndex, bool);
	std::shared_ptr<DynamicMesh<VertexColor>> m_mesh;
	std::shared_ptr<DynamicMesh<Vertex3D>> m_meshItem;
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
	float m_initialSlope;
	std::vector<std::vector<RoadSection>> m_roadInfo;
	float m_roadWidth;
	int m_vindex;
	// number of points per band
	long m_n;
	float m_oldy;
	int m_oldis;
	std::map<long, float> m_branchOffset;
	float m_z0;
	int m_imax;
	std::unordered_map<int, std::vector<RoadItem>> m_roadItems;
	std::unordered_map<int, QuadInfo> m_quadInfo;

	// colors
	glm::vec4 m_roadColors[2];
	glm::vec4 m_terrainColors[2];
	glm::vec4 m_stripeColor;

};



inline std::type_index Road::GetType() {
    return std::type_index(typeid(Road));
}


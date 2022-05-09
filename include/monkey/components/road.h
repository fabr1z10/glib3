#pragma once

#include <monkey/component.h>
#include <monkey/components/inputmethod.h>
#include <monkey/dynamicmesh.h>

class RoadSection {
public:
    RoadSection(long s0, long steps, float width, float curvature, float slope, float offset)
        : s0(s0), steps(steps), width(width), curvature(curvature), slope(slope), offset(offset) {}
	long getStartIndex() const;

    // start and end of the section
    long s0;
    long steps;
    float width;
    float curvature;
    float slope;
    float offset;
    //int next;
};

struct RoadNode {
	RoadNode() : startIndex(0), length(0), endIndex(0) {}
	long startIndex;
	long length;
	long endIndex;
	std::vector<std::shared_ptr<RoadSection>> sections;
};


struct RoadItem {
	float s;
	float x;
	float scale;
	std::string model;
	bool flip;
};

inline long RoadSection::getStartIndex() const {
	return s0;
}

class SimpleSection : public RoadSection {
public:
    SimpleSection(long s0, long s1, float width, float curvature, float slope, float offset) :
        RoadSection(s0, s1, width, curvature, slope, offset) {}

};

class Fork : public RoadSection {

};




class Road : public Component {
public:
    Road(const ITab&);
    void Start() override;
	void Update(double) override;
private:
	int addStep(std::vector<VertexColor>&, std::vector<unsigned>&, float x, float y, float z, float width, unsigned colorIndex, float dx, float dy, float step);
	float m_speed;
	float m_acceleration;
	// position of the player in the road (distance from beginning)
    float m_s;
    int m_branch;
	int m_lastIndex;
	float m_camx;
    /// the width of each step in a road section (along z)
    float m_step;

    // colors
    glm::vec4 m_roadColors[2];
    glm::vec4 m_terrainColors[2];
    glm::vec4 m_stripeColor;

    InputMethod * m_input;
    Camera* m_cam;

    std::vector<int> m_pathTaken;
	int m_lastNodeIndex;
	int m_lastSectionIndex;

    std::shared_ptr<DynamicMesh<VertexColor>> m_mesh;
    std::shared_ptr<DynamicMesh<Vertex3D>> m_meshItem;
    std::vector<RoadNode> m_roadTree;
    Entity* m_car;
	std::map<float, std::vector<RoadItem>>::iterator m_roadItemIterator;
    std::map<float, std::vector<RoadItem>> m_roadItems;

    // current items
    std::list<std::pair<glm::vec2, Entity*>> m_currentItems;

};
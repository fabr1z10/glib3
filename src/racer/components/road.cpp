#include "road.h"
#include <GLFW/glfw3.h>
#include <monkey/scheduler.h>

#include <monkey/engine.h>
#include <iostream>
#include <monkey/entities/sprite.h>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/shortestpath.h>
#include <monkey/properties.h>
#include <monkey/meshfactory.h>
#include <monkey/components/basicrenderer.h>
#include <monkey/quadmesh.h>

//WalkArea::WalkArea(std::shared_ptr<IShape> shape, int priority) : ScriptHotSpot(shape, priority) {}

Road::Road(const ITab& t) : Component(t) {

//	m_n = 2;
	m_s = 0.0f;
//	m_d0 = 5.0f;
//	m_step = m_d0 / m_n;
//	m_z0 = 0.0f;

    // z increment between a point and the next
    m_step = 2.5f;

    // number of points for each color
    m_n = 1;

}


void Road::Start() {
    // init mesh
    m_imax=0;
    m_oldy = 0.0f;
    std::cerr << "qu]m";
	m_oldis = -10;
	m_oldy = 0.0f;
    m_speed = 0.0f;
	m_acceleration= 10.0f;

	m_roadColors[0] = glm::vec4(156, 156, 156, 255) / 255.0f;
	m_roadColors[1] = glm::vec4(148, 148, 148, 255) / 255.0f;
	m_terrainColors[1] = glm::vec4(239, 222, 208, 255) / 255.0f;
	m_terrainColors[0] = glm::vec4(230, 214, 197, 255) / 255.0f;
	m_stripeColor = glm::vec4(247, 247, 247, 255) / 255.0f;


	m_input = m_entity->GetComponent<InputMethod>();
	if (m_input == nullptr) {
		GLIB_FAIL("Road requires an <InputMethod> component!");
	}
	m_cam = Monkey::get().Get<Camera>("maincam");

	m_quadInfo[0] = {{0, 0, 78, 168}, {61, 164}};

	for (int i = 2; i < 1000; ++i) {
        m_roadItems[i].push_back(RoadItem{-3.0f, 3.0f, 0,true});
        m_roadItems[i].push_back(RoadItem{3.0f, 3.0f, 0,false});
    }

    m_mesh = std::make_shared<DynamicMesh<VertexColor>>(COLOR_SHADER);
    m_meshItem = std::make_shared<DynamicMesh<Vertex3D>>(TEXTURE_SHADER_UNLIT);
    auto texName = "gfx/or.png";
    m_meshItem->setTexture(texName);
    auto tex = Engine::get().GetAssetManager().GetTex(texName);

    for (auto& quad : m_quadInfo) {
        quad.second.offset.x = (quad.second.offset.x - quad.second.loc.x) / quad.second.loc.z;
        quad.second.offset.y = (quad.second.loc.y + quad.second.loc.w - quad.second.offset.y) / quad.second.loc.w;
        quad.second.loc.x /= tex->GetWidth();
        quad.second.loc.y /= tex->GetHeight();
        quad.second.loc.z /= tex->GetWidth();
        quad.second.loc.w /= tex->GetHeight();


    }

    m_mesh->m_primitive = GL_TRIANGLES;
    m_meshItem->m_primitive = GL_TRIANGLES;
    //m_entity->AddComponent(std::make_shared<BasicRenderer>())
    auto model = std::make_shared<BasicModel>(m_mesh);
    auto model2 = std::make_shared<BasicModel>(m_meshItem);
	auto renderer = std::make_shared<BasicRenderer>(model);
	auto renderer2 = std::make_shared<BasicRenderer>(model2);
	auto itemEntity = std::make_shared<Entity>();
	itemEntity->AddComponent(renderer2);
	m_entity->AddComponent(renderer);
	m_entity->AddChild(itemEntity);
	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;
	float roadWidth = 2.0f;
	int n = 200;
	for (int i = 0; i < n; ++i) {
		vertices.emplace_back(-roadWidth, 0.0f, -i);
		vertices.emplace_back(roadWidth, 0.0f, -i);
	}
	for (int i = 0; i < n; ++i) {
		indices.push_back(i);
		indices.push_back(i+2);
		indices.push_back(i+1);
		indices.push_back(i+3);
	}
	m_curvature=0.0f;
	m_initialSlope=0.0f;
	// road 1
	std::vector<RoadSection> r1;
	r1.push_back(RoadSection(0, 20, roadWidth, 0.0f, 0.0f, 0.0f));
	r1.push_back(RoadSection(20, 200, roadWidth, 0.01f, 0.0f, 0.0f));
	r1.push_back(RoadSection(200, 900, roadWidth, -0.01f, 0.01f, 0.0f));
	r1.push_back(RoadSection(900, 1000, roadWidth, 0.0f, 0.0f, 0.0f));
	m_roadInfo.push_back(r1);

	std::vector<RoadSection> r2;
	r2.push_back(RoadSection(10, 500, roadWidth, -0.01f, 0.0f, 0.0f));
//	r2[5000] = RoadSection(roadWidth, 0.0f, 0.01f, 0.0f);
	//m_roadInfo.push_back(r2);

	m_branchOffset[r2.begin()->begins] = 0.0f;
	size_t i = r2.begin()->begins;
	size_t csection = 0;
	float offset{0.0f};
	float dx{0.0f};
	while (true) {
	    i++;
	    dx += r2[csection].curvature * m_step;
	    offset += dx;
	    m_branchOffset[i] = offset;
	    if (i==r2[csection].ends) {
	        break;
	    }
	}
//
//	float s0 = r2.begin()->first;
//
//	size_t i {0};
//	auto csection = r2.begin()->second;
//    float current_offset{0.0f};
//	m_branchOffset[i++] = current_offset;
//	while (true) {
//	    current_offset += csection.curvature * m_step;
//	    m_branchOffset[i++] = current_offset;
//	}

	// end road 1
	//m_step = 0.01f;

	// road 2
//	m_roadInfo[-10] = std::make_pair(0, 0);
//	m_roadInfo[50] = std::make_pair(0, 0.01f);
//	m_roadInfo[200] = std::make_pair(0, 0.0f);
//	m_roadInfo[300] = std::make_pair(0, 0.01f);
//	m_roadInfo[400] = std::make_pair(0, -0.01f);
//	m_roadInfo[500] = std::make_pair(0, 0.01f);
//	m_roadInfo[800] = std::make_pair(0, 0.01f);
//	m_roadInfo[1000] = std::make_pair(0, 0.0f);
//	m_roadInfo[10000] = std::make_pair(0, 0.0f);
	// end road 2
//	m_roadInfo[500] = std::make_pair(0, -0.01f);
//	m_roadInfo[600] = std::make_pair(0, 0.01f);
//	m_roadInfo[700] = std::make_pair(0, -0.01f);
//	m_roadInfo[800] = std::make_pair(0, 0.01f);
//	m_roadInfo[500] = std::make_pair(-0.000001, 0);
//	m_roadInfo[900] = std::make_pair(0, 0);
	//m_mesh->UpdateGeometry(vertices, indices);
}

void Road::Update(double dt) {
	if (m_input->isKeyDown(GLFW_KEY_UP)) {
		m_speed += m_acceleration * dt;
	} else if (m_input->isKeyDown(GLFW_KEY_DOWN)) {
		m_speed -= m_acceleration * dt;
		m_speed = std::max(0.0f, m_speed);
	}
    auto pos = m_cam->GetPosition();
	if (m_input->isKeyDown(GLFW_KEY_LEFT)) {
		pos.x -= 0.2f*m_speed*dt;
	} else if (m_input->isKeyDown(GLFW_KEY_RIGHT)) {
		pos.x += 0.2f*m_speed*dt;
	}

	// advance car position
	float ds = dt * m_speed;
	m_s += ds;
	pos.z = -m_s;


	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;
    std::vector<Vertex3D> verticesItems;
    std::vector<unsigned> indicesItems;
	// number of points to draw (in -z direction)
	int n{200};

	float roadWidth{2.0f};
	//std::array<glm::vec4, 2> colors = { glm::vec4(0.64, 0.64, 0.64, 1.0f), glm::vec4(0.32,0.32f,0.32f,1.0)};

	unsigned k = 0;



	// draw all roads (1st road is the main, other are branches)
	int roadIndex = -1;
    long j0 = int(m_s / m_step);
    long j1 = j0 + n;
    std::unordered_map<int, glm::vec3> pts;
	for (const auto& road : m_roadInfo) {
	    roadIndex++;
        // get first index to be drawn:
        long i0 = int(m_s / m_step);
		long r0 = road.front().begins;
		long re = road.back().ends;
		if (i0 > re) {
		    // road is behind. don't draw anything
		    continue;
		}
		float z0{-m_s};
		float dfirst = m_step;
		long i = i0;
		size_t currentSection{0};
		bool startsAhead= false;
		if (r0 > i0) {
		    // road starts ahead
		    i = r0;
		    z0 = - (r0 * m_step );
		    i0 = r0;
		    startsAhead =true;
		} else {
		    i = i0;
		    dfirst = (i0 + 1) * m_step - m_s;
		    for (size_t j = 0; j< road.size(); ++j) {
		        if (road[j].ends > i0) {
		            currentSection = j;
		            break;
		        }
		    }
		}
        auto current_color = long(i0/m_n) % 2;
		float rx = 0.0f;
		if (roadIndex > 0 && !startsAhead) {
		    float pct = (m_s - i0 * m_step)/m_step;
		    rx = pct * m_branchOffset[i0+1] + (1.0-pct)*m_branchOffset[i0];
		    std::cerr << i0 << " @ " << rx << "\n";

		}
		//float rx = roadIndex == 0 ? 0 : m_branchOffset[i0];
		float ry = 0;
        k = vertices.size();

        // place the first two points

        vertices.emplace_back(rx - roadWidth, ry, z0, m_roadColors[current_color] * glm::vec4(1.0f));
        vertices.emplace_back(rx + roadWidth, ry, z0, m_roadColors[current_color]);
		vertices.emplace_back(rx + roadWidth, ry, z0, m_terrainColors[current_color]);
		vertices.emplace_back(rx + roadWidth+ 50.0f, ry, z0, m_terrainColors[current_color]);
		vertices.emplace_back(rx - roadWidth-50.0f, ry, z0, m_roadColors[current_color]);
		vertices.emplace_back(rx - roadWidth, ry, z0, m_roadColors[current_color]);

        auto* cs = &road[currentSection];
        pos.x -= 5*ds * cs->curvature;
        float dx = 0.0f;
        float dy = 0.0f;
        float z = z0;
		while (i < j1) {
            float step = (i == i0 ? dfirst : m_step);
            dx += step * cs->curvature;
            dy += step * cs->slope;
            rx += dx;
            ry += dy;
            z -= step;
            if (roadIndex > 0) {
                float pct = (m_s - i * m_step)/m_step;
                rx = m_branchOffset[i];
            }
            pts[i] = glm::vec3(rx, ry, z);
            vertices.emplace_back(rx - roadWidth, ry, z, m_roadColors[current_color]);
            vertices.emplace_back(rx + roadWidth, ry, z, m_roadColors[current_color]);
			vertices.emplace_back(rx + roadWidth, ry, z, m_terrainColors[current_color]);
			vertices.emplace_back(rx + roadWidth+ 50.0f, ry, z, m_terrainColors[current_color]);
			vertices.emplace_back(rx - roadWidth - 50.0f, ry, z, m_terrainColors[current_color]);
			vertices.emplace_back(rx - roadWidth, ry, z, m_terrainColors[current_color]);
            indices.push_back(k);
            indices.push_back(k + 1);
            indices.push_back(k + 6);
            indices.push_back(k + 7);
            indices.push_back(k + 6);
            indices.push_back(k + 1);

            indices.push_back(k + 2);
			indices.push_back(k + 3);
			indices.push_back(k + 8);
			indices.push_back(k + 9);
			indices.push_back(k + 8);
			indices.push_back(k + 3);

			indices.push_back(k + 4);
			indices.push_back(k + 5);
			indices.push_back(k + 10);
			indices.push_back(k + 11);
			indices.push_back(k + 10);
			indices.push_back(k + 5);

            k += 6;
            auto this_color = long(i/m_n) % 2;
            if (this_color != current_color) {
                current_color = this_color;
                vertices.emplace_back(rx - roadWidth, ry, z, m_roadColors[current_color]);
                vertices.emplace_back(rx + roadWidth, ry, z, m_roadColors[current_color]);
				vertices.emplace_back(rx + roadWidth, ry, z, m_terrainColors[current_color]);
				vertices.emplace_back(rx + roadWidth +50.f, ry, z, m_terrainColors[current_color]);
				vertices.emplace_back(rx - roadWidth-50.0f, ry, z, m_terrainColors[current_color]);
				vertices.emplace_back(rx - roadWidth, ry, z, m_terrainColors[current_color]);

                k += 6;
            }
            i++;
            if (i > cs->ends) {
                // increment current section
                currentSection++;
                cs = &road[currentSection];
            }

            /// draw road items
            auto iter = m_roadItems.find(i);
            if (iter != m_roadItems.end()) {

                for (const auto& p : iter->second) {
                    // for every item, draw a quad
                    // start with bottom left and proceed ccw
                    auto n = verticesItems.size();
                    const auto& q = m_quadInfo.at(p.quadId);
                    auto width = p.height * (q.loc[2]/(static_cast<float>(q.loc[3])));
                    float txl = q.loc[0];
                    float txr = q.loc[0] + q.loc[2];
                    float tx0 = p.flipH ? txr : txl;
                    float tx1 = p.flipH ? txl : txr;
                    float ox = p.flipH ? (1.0f - q.offset[0]) * width : q.offset[0] * width;
                    float oy = q.offset[1] * p.height;
                    verticesItems.emplace_back(rx - ox + p.x, ry - oy, z, tx0, q.loc[1]+q.loc[3]);
                    verticesItems.emplace_back(rx - ox + p.x + width, ry - oy, z, tx1, q.loc[1]+q.loc[3]);
                    verticesItems.emplace_back(rx - ox + p.x + width, ry - oy + p.height, z,tx1, q.loc[1]);
                    verticesItems.emplace_back(rx - ox + p.x, ry - oy + p.height, z, tx0, q.loc[1]);
                    indicesItems.emplace_back(n);
                    indicesItems.emplace_back(n+1);
                    indicesItems.emplace_back(n+2);
                    indicesItems.emplace_back(n+2);
                    indicesItems.emplace_back(n+3);
                    indicesItems.emplace_back(n);

                }
            }
		}

	}
	m_cam->SetPosition(pos, glm::vec3(0,0,-1), glm::vec3(0,1,0));

    // check new objects between imax and i
//    if (j1 > m_imax) {
//        std::cerr << "checking new objects between @" << m_imax << " and " << j1 << "\n";
//        for (int i = m_imax; i < j1; ++i) {
//            auto iter = m_roadItems.find(i);
//            if (iter != m_roadItems.end()) {
//                for (const auto& p : iter->second) {
//                    auto entity = std::make_shared<Entity>();
//                    auto cx = pts.at(i);
//                    entity->SetPosition(glm::vec3(cx.x + p.x, cx.y, cx.z));
//                    auto mesh = std::make_shared<QuadMesh>("gfx/block1.png", 2.0f, 2.0f, 1.0f, 1.0f, 0.0f, 0.0f, glm::vec2(-1.0f, 0.0f));
//                    auto rend = std::make_shared<BasicRenderer>(std::make_shared<BasicModel>(mesh));
//                    entity->AddComponent(rend);
//                    entity->SetTag("[alma");
//                    m_entity->AddChild(entity);
//                }
//            }
//        }
//        m_imax = j1;
//    }
	m_mesh->UpdateGeometry(vertices, indices);
    m_meshItem->UpdateGeometry(verticesItems, indicesItems);
}


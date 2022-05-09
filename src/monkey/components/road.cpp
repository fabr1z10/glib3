#include <monkey/components/road.h>
#include <monkey/entity.h>
#include <monkey/components/renderer.h>
#include <monkey/scenefactory.h>

Road::Road(const ITab& t) : Component(t) {

    m_s = 0.0f;

    // z increment between a point and the next
    //m_step = 2.5f;

    // number of points for each color
    //m_n = 1;

    // initial colors
    m_roadColors[0] = t.get<glm::vec4>("road_color_0", glm::vec4(156, 156, 156, 255) / 255.0f);
    m_roadColors[1] = t.get<glm::vec4>("road_color_1", glm::vec4(148, 148, 148, 255) / 255.0f);
    m_terrainColors[0] = t.get<glm::vec4>("terrain_color_0", glm::vec4(230, 214, 197, 255) / 255.0f);
    m_terrainColors[1] = t.get<glm::vec4>("terrain_color_1", glm::vec4(239, 222, 208, 255) / 255.0f);
    m_stripeColor = t.get<glm::vec4>("stripe_color", glm::vec4(247, 247, 247, 255) / 255.0f);
	m_step = 0.25f;

	m_speed = 0.0f;
	m_acceleration= 10.0f;
	m_branch= 0;
	m_camx=0.0f;

	t.foreach("items", [&] (const ITab& u) {
		auto model = u.get<std::string>("model");
		auto x = u.get<float>("x");
		auto delta = u.get<float>("delta", m_step);
		auto count = u.get<int>("count", 1);
		auto scale = u.get<float>("scale");
		auto s = u.get<float>("start");
		bool flip = u.get<bool>("flip", false);
		for (size_t i = 0; i < count; ++i) {
			m_roadItems[s].push_back(RoadItem{s, x, scale, model, flip});
			//m_roadItems[5.0].push_back(RoadItem{6.0, 0.0f, 0.01f, "01.palm"});
			s += delta;
		}
	});

	t.foreach("road", [&] (const ITab& u) {
		// create a new road node
		RoadNode node;
		int parent = t.get<int>("parent", -1);
		node.startIndex = (parent == -1 ? 0 : m_roadTree[parent].endIndex);
		int j = node.startIndex;
		u.foreach("sections", [&](const ITab &v) {
			auto sectionType = v.get<std::string>("type");
			if (sectionType == "road") {
				int length = v.get<int>("length");
				float width = v.get<float>("width");
				float curve = v.get<float>("curve");
				float slope = v.get<float>("slope");
				node.sections.push_back(std::make_shared<RoadSection>(j, length, width, curve, slope, 0.0f));
				j += length;
				node.length += length;
				node.endIndex = node.startIndex + node.length;
			}
		});
		m_roadTree.push_back(node);
	});



	m_roadItemIterator = m_roadItems.begin();

//		node.push_back(std::make_shared<RoadSection>(0, 200, roadWidth, 0.01f, 0.001f, 0.0f));
//		//node.push_back(std::make_shared<RoadSection>(200, 200, roadWidth*0.6, 0.0f, 0.0f, 0.0f));
//		//node.push_back(std::make_shared<RoadSection>(200, 200, roadWidth, 0.01f, 0.0f, 0.0f));
//		node.push_back(std::make_shared<RoadSection>(200, 200, roadWidth, 0.0f, -0.001f, 0.0f));
//		node.push_back(std::make_shared<RoadSection>(400, 200, roadWidth, -0.005f, -0.0005f, 0.0f));
//		node.push_back(std::make_shared<RoadSection>(600, 800, roadWidth, 0.0f, 0.0f, 0.0f));
//		m_roadTree.push_back(node);
//	});
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



	// number of points to draw (in -z direction)
	int n{200};

	float sStart = m_s;
 	float sEnd = m_s + n * m_step;

	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;

	// find 1st index to draw
	long j0 = int(m_s / m_step);
	float z0 = m_s - j0 * m_step;
	float z_size_of_first = (j0 + 1) * m_step - m_s;

	//std::unordered_map<int, glm::vec3> pts;
	if (m_lastNodeIndex == -1) {
		return;
	}
	const auto& node = m_roadTree[m_lastNodeIndex];
	auto currentBranch = node.sections[m_lastSectionIndex];
	long s1 = currentBranch->s0 + currentBranch->steps;
	if (j0 >= s1) {
		m_lastSectionIndex++;
		if (m_lastSectionIndex >= node.sections.size()) {
			m_lastSectionIndex = -1;
			return;
		}
		currentBranch = node.sections[m_lastSectionIndex];
		s1 = currentBranch->s0 + currentBranch->steps;
	}
	float rx = 0.0f;
	float ry = 0.0f;
	auto width = 1.0f;
	//addStep(vertices, indices, rx, ry, z0, width, current_color);
	float z = 0;
	int stepCount{0};
	int maxSteps{200};
	int currentIndex = m_lastSectionIndex;
	float dx = 0.0f;
	float dy = 0.0f;

	std::map<float, float> z_to_y;
	glm::vec3 cpos = m_car->GetPosition();
	float shift_car_y = 0.0;
	std::unordered_map<float, glm::vec3> jpos;
	while (stepCount < maxSteps) {
		for (long j = j0; j < s1 && stepCount < maxSteps; ++j) {
			auto current_color = j % 2;
			float step = (stepCount == 0 ? z_size_of_first : m_step);
			dx += step * currentBranch->curvature;
			dy += step * currentBranch->slope;
			jpos[j] = glm::vec3(rx, ry, z);
			addStep(vertices, indices, rx, ry, z, currentBranch->width, current_color, dx, dy, step);
			z_to_y[z] = ry;
			rx += dx;
			ry += dy;
			stepCount++;
			z -= step;
		}
		if (currentIndex < node.sections.size() - 1) {
			currentIndex++;
			currentBranch = node.sections[currentIndex];
			j0 = currentBranch->s0;
			s1 = currentBranch->s0 + currentBranch->steps;
		} else {
			break;
		}
	}
	auto iter = z_to_y.lower_bound(-1.5f);

	m_car->SetPosition(glm::vec3(cpos.x, shift_car_y, cpos.z));

	// handle items. Create / update / delete sprites
	// advance until position > sEnd

	/// 1. part 1 advance iterator and create new items
	auto factory = Engine::get().GetSceneFactory();

	while (m_roadItemIterator != m_roadItems.end() && m_roadItemIterator->first <= sEnd) {
		// create a new item
		for (const auto& item : m_roadItemIterator->second) {
			auto entity = std::make_shared<Entity>();
			int jItem = item.s / m_step;
			glm::vec3 zeroPos = jpos[jItem] + (jpos[jItem+1] - jpos[jItem]) * (item.s - jItem * m_step);
			zeroPos.x += item.x;
			entity->SetPosition(zeroPos);
			auto model = Engine::get().GetAssetManager().get<Model>(item.model);
			auto renderer = model->makeRenderer(model);
			entity->AddComponent(model->makeRenderer(model));
			entity->SetScale(item.scale);
			if (item.flip) {
				entity->SetFlipX(true);
			}
			m_entity->GetParent()->AddChild(entity);
			m_currentItems.push_back(std::make_pair(glm::vec2(item.s, item.x), entity.get()));
		}
		m_roadItemIterator++;
	}

	/// 2. update current items (move/remove)
	auto it = m_currentItems.begin();
	while (it != m_currentItems.end()) {
		float s = it->first[0];
		float x = it->first[1];
		if (s < sStart) {
			Engine::get().Remove(it->second);
			m_currentItems.erase(it++);
		} else {
			int jItem = s / m_step;
			glm::vec3 zeroPos = jpos[jItem] + (jpos[jItem+1] - jpos[jItem]) * (s - jItem * m_step);
			zeroPos.x += x;
			it->second->SetPosition(zeroPos);
			it++;
		}

	}


    glm::vec3 p(pos.x, 1, 1);
	m_cam->SetPosition(p, glm::vec3(0,0,-1), glm::vec3(0,1,0));

	m_mesh->UpdateGeometry(vertices, indices);
}

void Road::Start() {
	m_car = Monkey::get().Get<Entity>("car");
	m_lastNodeIndex = 0;
	m_lastSectionIndex = 0;
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("Road requires an <InputMethod> component!");
    }
    m_cam = Monkey::get().Get<Camera>("maincam");

    m_mesh = std::make_shared<DynamicMesh<VertexColor>>(COLOR_SHADER);

    m_mesh->m_primitive = GL_TRIANGLES;

    auto model = std::make_shared<Model>(m_mesh);
    auto renderer = model->makeRenderer(model);
    m_entity->AddComponent(renderer);

    //float roadWidth = 1.0f;

//    std::vector<std::shared_ptr<RoadSection>> node;
//    node.push_back(std::make_shared<RoadSection>(0, 200, roadWidth, 0.01f, 0.001f, 0.0f));
//	//node.push_back(std::make_shared<RoadSection>(200, 200, roadWidth*0.6, 0.0f, 0.0f, 0.0f));
//	//node.push_back(std::make_shared<RoadSection>(200, 200, roadWidth, 0.01f, 0.0f, 0.0f));
//	node.push_back(std::make_shared<RoadSection>(200, 200, roadWidth, 0.0f, -0.001f, 0.0f));
//	node.push_back(std::make_shared<RoadSection>(400, 200, roadWidth, -0.005f, -0.0005f, 0.0f));
//	node.push_back(std::make_shared<RoadSection>(600, 800, roadWidth, 0.0f, 0.0f, 0.0f));
//	m_roadTree.push_back(node);
}

int Road::addStep(std::vector<VertexColor>& vertices, std::vector<unsigned int>& indices,
						  float x, float y, float z, float width, unsigned colorIndex, float dx, float dy, float step) {
	unsigned nv = vertices.size();
	float darken = 1.0f ; //exp(0.002f*(z+m_s));
	glm::vec4 multiply (darken, darken, darken, 1.0f);
	vertices.emplace_back(x - width, y, z, m_roadColors[colorIndex] * darken);
	vertices.emplace_back(x + width, y, z, m_roadColors[colorIndex] * darken);
	vertices.emplace_back(x + width, y, z, m_terrainColors[colorIndex]* darken);
	vertices.emplace_back(x + width + 50.0f, y, z, m_terrainColors[colorIndex]*darken);
	vertices.emplace_back(x - width - 50.0f, y, z, m_terrainColors[colorIndex]*darken);
	vertices.emplace_back(x - width, y, z, m_terrainColors[colorIndex]*darken);

	vertices.emplace_back(x - width + dx, y + dy, z - step, m_roadColors[colorIndex] * darken);
	vertices.emplace_back(x + width + dx, y +dy, z - step, m_roadColors[colorIndex] * darken);
	vertices.emplace_back(x + width + dx, y+dy, z - step, m_terrainColors[colorIndex]* darken);
	vertices.emplace_back(x + width + dx + 50.0f, y+dy, z - step, m_terrainColors[colorIndex]*darken);
	vertices.emplace_back(x - width + dx- 50.0f, y+dy, z - step, m_terrainColors[colorIndex]*darken);
	vertices.emplace_back(x - width + dx, y+dy, z - step, m_terrainColors[colorIndex]*darken);

	auto o = vertices.size();
		indices.push_back(o);
		indices.push_back(o+1);
		indices.push_back(o+6);
		indices.push_back(o+1);
		indices.push_back(o+7);
		indices.push_back(o+6);

		indices.push_back(o+2);
		indices.push_back(o+3);
		indices.push_back(o+8);
		indices.push_back(o+3);
		indices.push_back(o+9);
		indices.push_back(o+8);

		indices.push_back(o+4);
		indices.push_back(o+5);
		indices.push_back(o+10);
		indices.push_back(o+5);
		indices.push_back(o+11);
		indices.push_back(o+10);

}
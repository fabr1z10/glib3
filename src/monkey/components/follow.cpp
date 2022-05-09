#include <monkey/components/follow.h>
#include <monkey/engine.h>
#include <iostream>

Follow::Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up) :
Component(), m_camId{cam}, m_relativePos(relativePos), m_up(up), m_fixZ{false}
{
    //m_dir = -glm::normalize(m_relativePos);
    m_dir = glm::vec3(0,0, -1);
}

void Follow::Begin() {
	glm::vec3 pos = m_entity->GetPosition();
	glm::vec3 eye = pos + m_relativePos;
	if (m_fixZ) {
		eye.z = m_z;
	}
	m_cam->SetPosition(eye, m_dir, m_up);
	m_previousPosition = pos;

}

Follow::Follow(const ITab & t) : Component(t), m_fixZ{false} {
    m_dir = glm::vec3(0,0, -1);

    m_camId = t.get<std::string>("cam");
    m_relativePos = t.get<glm::vec3>("relativepos");
    m_up = t.get<glm::vec3>("up");
    if (t.has("z")) {
        float z = t.get<float>("z");
        fixZ(z);
    }
}

DynamicFollow::DynamicFollow(const ITab& t) : Follow(t) {



	auto origin = t.get<glm::vec2>("origin");
	auto path = t.get<std::vector<int>>("path");
	glm::vec2 p = origin;
	for (size_t i = 0; i < path.size(); i += 2) {
	    int d = path[i];
	    int length = path[i+1];
	    switch (d) {
	        case 0:
                // down
                m_verticalWalls[p.x].push_back({p.x, p.y - length, p.y});
                p.y -= length;
                break;
            case 1:
                // left
                m_horizontalWalls[p.y].push_back({p.y, p.x - length, p.x});
                p.x -= length;
                break;
            case 2:
                // right
                m_horizontalWalls[p.y].push_back({p.y, p.x, p.x+ length});
                p.x += length;
                break;
            case 3:
                // up
                m_verticalWalls[p.x].push_back({p.x, p.y, p.y + length});
                p.y += length;
                break;
	        default:
	            GLIB_FAIL("Unknwon direction " << d);

	    };



	}

}

void Follow::Start() {

    m_cam = Monkey::get().Get<Camera>(m_camId);


}


void DynamicFollow::Start() {
    Follow::Start();
    auto size = dynamic_cast<OrthographicCamera*>(m_cam)->GetSize();

    m_camHalfWidth = size.x * 0.5f;
    m_camHalfHeight = size.y * 0.5f;
}

void Follow::fixZ(float z) {
    m_fixZ = true;
    m_z = z;
}

void Follow::Update (double dt) {
    if (!m_active) return;
    glm::vec3 pos = m_entity->GetPosition();
    if (m_previousPosition - pos != glm::vec3(0.0f)) {
        glm::vec3 eye = pos + m_relativePos;
        if (m_fixZ) {
            eye.z = m_z;
        }



        // eye.y = 10;
        //std::cout << "Update cam pos to " << pos.x << ", " << pos.y << "\n";
        m_cam->SetPosition(eye, m_dir, m_up);

    }
	m_previousPosition = pos;
}

//         |  cw			 if x_player <= cw
// x_cam = |  ww - cw		 if x_player >= ww - cw
//         |  x_player		 otherwise


std::pair<bool, float> DynamicFollow::checkBounds(float halfSize, decltype(m_verticalWalls.begin()) iter,
                                                  decltype(m_verticalWalls.begin()) end, float z, float k, bool fwd) const {
    float cum_dist {0.0f};
    float z_curr = z;
    while (cum_dist < halfSize && iter != end) {
        cum_dist += fabs(z_curr - iter->first);
        z_curr = iter->first;
        for (const auto& wall : iter->second) {
            if ((wall.max < k - halfSize || wall.min > k + halfSize)) {
                // no coll, nothing to do
            } else {
                // collide
                if (fabs(z - iter->first) > halfSize) {
                    return {false, z};
                } else {
                    return {true, iter->first + (iter->first < z ? halfSize : -halfSize)};
                }
            }
        }
        if (fwd) ++iter; else --iter;
    }
    return {false, z};

}

std::pair<decltype(DynamicFollow::m_verticalWalls.begin()), decltype(DynamicFollow::m_verticalWalls.begin())>
        DynamicFollow::getIterators(std::map<float, std::vector<ScrollBound>>& m, float z) {
    auto igreater = m.lower_bound(z);
    if (igreater == m_verticalWalls.end()) {
        // all walls are LEFT of camera, so we need to position camera left of last wall
        z = m.rend()->first - 0.01f;
        igreater = m_verticalWalls.lower_bound(z);
    }
    if (igreater == m_verticalWalls.begin()) {
        // all walls are RIGHT OF cam, so we need to position cam right of first wall
        z = m.begin()->first + 0.01f;
        igreater = m_verticalWalls.lower_bound(z);
    }
    auto iless = igreater;
    iless--;
    return std::make_pair(iless, igreater);
}

void DynamicFollow::Update (double dt) {
	if (!m_active) return;
	glm::vec3 pos = m_entity->GetPosition();

	if (m_previousPosition - pos != glm::vec3(0.0f)) {
		float yplayer = pos.y -0.707106781186548 * pos.z;
		float xCam = pos.x;
		float yCam = yplayer;
		float zCam = 0.01*pos.z;

		auto xiter = getIterators(m_verticalWalls, xCam);
        auto yiter = getIterators(m_horizontalWalls, yCam);

		auto xwall = checkBounds(m_camHalfWidth, xiter.first, m_verticalWalls.begin(), xCam, yCam, false);
		if (!xwall.first)
            xwall = checkBounds(m_camHalfWidth, xiter.second, m_verticalWalls.end(), xCam, yCam, true);
		if (fabs(xCam - xwall.second) > 1.0f) {
		    std::cerr << "pane";
		}
		xCam = xwall.second;
        auto ywall = checkBounds(m_camHalfHeight, yiter.first, m_horizontalWalls.begin(), yCam, xCam, false);
        if (!ywall.first)
            ywall = checkBounds(m_camHalfHeight, yiter.second, m_horizontalWalls.end(), yCam, xCam, true);
        yCam = ywall.second;
        glm::vec3 eye = glm::vec3(xCam, yCam, zCam) + m_relativePos;
        if (m_fixZ) {
            eye.z = m_z;
        }
        m_cam->SetPosition(eye, m_dir, m_up);
	}
	m_previousPosition = pos;
}
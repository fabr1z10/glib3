#include <monkey/component.h>
#include <monkey/camera.h>


class Follow : public Component {
public:
    Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up);
    Follow (const ITab&);
    void Start() override;
    void Begin() override;
    void Update(double) override;
    void fixZ(float);
    using ParentClass = Follow;
protected:
	glm::vec3 m_relativePos;
	glm::vec3 m_previousPosition;
	float m_z;
	Camera* m_cam;
	bool m_fixZ;
	glm::vec3 m_dir;
	glm::vec3 m_up;

private:
	std::string m_camId;
    // relative position of camera w.r.t. target

};

class DynamicFollow : public Follow {
public:
	DynamicFollow(const ITab&);
	void Update(double) override;

private:
	float m_camHalfWidth;
	float m_camHalfHeight;
	float m_worldWidth;
	float m_x0, m_x1;
	std::map<float, glm::vec2> m_dynamicCamBounds;
};

#include <monkey/mesh.h>


class SkeletalMesh : public Mesh<VertexSkeletal> {
public:
	SkeletalMesh();
	glm::vec2 getOrigin() const;
	void setOrigin(glm::vec2);
	glm::vec2 getKeyPoint(const std::string&) const;
	glm::vec2 getDimension(const std::string&) const;
	void addKeyPoint(const std::string& id, glm::vec2);
	void addDimension(const std::string& id, glm::vec2);
private:
	glm::vec2 m_origin;
	std::unordered_map<std::string, glm::vec2> m_keyPoints;
	std::unordered_map<std::string, glm::vec2> m_dimensions;
};


inline glm::vec2 SkeletalMesh::getOrigin() const {
	return m_origin;
}

inline void SkeletalMesh::setOrigin(glm::vec2 P) {
	m_origin = P;
}

inline void SkeletalMesh::addKeyPoint(const std::string &id, glm::vec2 P) {
	m_keyPoints[id] = P;
}

inline void SkeletalMesh::addDimension(const std::string &id, glm::vec2 P) {
	m_dimensions[id] = P;
}
inline glm::vec2 SkeletalMesh::getKeyPoint(const std::string& id) const {
	return m_keyPoints.at(id);
}

inline glm::vec2 SkeletalMesh::getDimension(const std::string& id) const {
	return m_dimensions.at(id);
}
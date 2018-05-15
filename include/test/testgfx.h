#include <gfx/engine.h>
#include <test/solution.h>

class Factory1 : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
};

struct StationLocation {
    float x, y;
};

struct ResourceLocation {
    std::vector<glm::vec2> pts;
};

class Factory2 : public SceneFactory {
public:
    Factory2(Solution& s) : m_solution(s){}
    std::shared_ptr<Entity> Create() override;
    void DrawLineStemmingFrom(int stationId, float x, float y);
    void RefreshTrains(double t);
private:
    Entity* m_trainNode;

    std::unordered_map<int, StationLocation> m_stations;
    std::unordered_map<int, ResourceLocation> m_loc;
    Solution& m_solution;
    std::unordered_map<int, std::vector<int>> connections;
    std::unordered_set<int> done;
    std::unordered_map<std::string, bool> trainDir;
};
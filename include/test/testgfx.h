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

/**
    Utility library class for translation of Absolute Times (linux-like) to human-readable string.
    All sec are since 00:00 hours, of a predefined start date (usualy Jan 1, 1970 UTC or local time).
    Usage: prior to instancing a TimeFormatter object user should call the static method SetReferenceDay.
    Warning: due to the static reference day the class is not completely thread-safe.
*/



class Factory2 : public SceneFactory {
public:
    Factory2(Solution& s) : m_solution(s){}
    std::shared_ptr<Entity> Create() override;
    void DrawLineStemmingFrom(int stationId, float x, float y);
    void RefreshTrains(double t);
    std::shared_ptr<Entity> CreateLabel (const std::string&, glm::vec4 color, glm::vec2 pos, float size, int layer = 1);
private:
    Entity* m_trainNode;

    std::unordered_map<int, StationLocation> m_stations;
    std::unordered_map<int, ResourceLocation> m_loc;
    Solution& m_solution;
    std::unordered_map<int, std::vector<int>> connections;
    std::unordered_set<int> done;
    std::unordered_map<std::string, bool> trainDir;
};
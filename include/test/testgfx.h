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

class Station;
class Entity;

struct Location {
    int i, j;
    int block;
};


class StationPlot;

class SceneFactory3 : public SceneFactory {
public:
    SceneFactory3(Solution& s) : sol(s) {}
    std::shared_ptr<Entity> Create() override;

    void CleanUp () override {}
private:
    Solution& sol;
    std::unordered_map<std::string, std::shared_ptr<StationPlot>> m_stations;
};

class StationPlot  {
public:
    StationPlot(const std::string&);
    std::shared_ptr<Entity> Get() {return gfxNode;}
    void ExtendFromPoint(Station& s, int id);
    std::shared_ptr<Entity> CreateLabel (const std::string& text, glm::vec4 color, glm::vec2 pos, float size);
    float GetWidth () const {return m_width*30.0f;}
    glm::vec2 GetTrackPosition(const std::string&) const;
    std::string GetStationId() {return m_stationId;}
private:
    void AddElement (Station& s, int point, int block);
    void AddConnection (Station& s, int point1, int point2);
    std::vector<glm::vec2> m_points;
    //std::shared_ptr<Entity> CreateLinePoint (x, y);
    //Entity* m_main;
    int m_blockMin;
    int m_startPoint;
    std::unordered_map<int, Location> locations;
    std::vector<std::pair<int,int>> m_edges;
    std::unordered_set<int> explored;
    std::string m_stationId;
    std::unordered_map<int, int> blockInfo;
    std::shared_ptr<Entity> gfxNode;
    int m_width;
    std::unordered_map<std::string, glm::vec2> m_linePointLocations;
};

inline glm::vec2 StationPlot::GetTrackPosition(const std::string& a) const {
    auto l = m_linePointLocations.find(a);
    if (l == m_linePointLocations.end())
        throw;
    return glm::vec2(gfxNode->GetPosition())+ l->second;
}

//class Factory2 : public SceneFactory {
//public:
//    Factory2(Solution& s) : m_solution(s){}
//    std::shared_ptr<Entity> Create() override;
//    void DrawLineStemmingFrom(int stationId, float x, float y);
//    void RefreshTrains(double t);
//    void CleanUp () override {}
//    std::shared_ptr<Entity> CreateLabel (const std::string&, glm::vec4 color, glm::vec2 pos, float size, int layer = 1);
//private:
//    Entity* m_trainNode;
//
//    std::unordered_map<std::string, StationLocation> m_stations;
//    std::unordered_map<std::string, ResourceLocation> m_loc;
//    Solution& m_solution;
//    std::unordered_map<int, std::vector<int>> connections;
//    std::unordered_set<int> done;
//    std::unordered_map<std::string, bool> trainDir;
//};
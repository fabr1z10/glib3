#pragma once

#include <unordered_map>
#include <memory>
#include <test/resource.h>
#include <gfx/singleton.h>

extern std::string homeDir;

class Railway {
public:
    Railway () {}
    void Load();
    int GetStationCount() const ;
private:
    std::unordered_map<std::string, std::shared_ptr<Station>> m_stations;
    std::unordered_map<std::string, std::shared_ptr<Station>> m_tracks;
};

inline int Railway::GetStationCount() const {
    return m_stations.size();
}


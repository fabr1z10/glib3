#pragma once

#include <unordered_map>
#include <memory>
#include <test/resource.h>
#include <gfx/singleton.h>

class Railway {
public:
    Railway () {}
    void Load();
    void ReadRunningTimes();
    int GetStationCount() const ;
    Station& GetStation(const std::string& name);
    Track& GetTrack(const std::string& name);

    std::vector<std::string> GetTracksConnecting (const std::string& A, const std::string& B);
private:
    std::unordered_map<std::string, std::shared_ptr<Station>> m_stations;
    std::unordered_map<std::string, std::shared_ptr<Track>> m_tracks;
};

inline int Railway::GetStationCount() const {
    return m_stations.size();
}


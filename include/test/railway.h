#pragma once

#include <unordered_map>
#include <memory>
#include <test/resource.h>
#include <gfx/singleton.h>


class Railway : public Singleton<Railway> {
public:
    int AddTrain (const std::string& name, int length, float speed);
    int AddStation (const std::string& name);
    int AddTrack (const std::string& name, int sa, int sb);
    int AddTrackCircuit (int trackId, const std::string& name, int length);
    //int AddStationRoute (int trackId, const std::string& name, int length);
    int AddStoppingPoint (int trackId, const std::string& name, int length);
    int GetStationCount() const;
    Track* GetTrack(const std::string&);
    Station* GetStation(const std::string&);
    Station* GetStation(int id);
    Track* GetTrack(int id);
    Train* GetTrain(const std::string&);
    int GetStoppingPointId (const std::string& station, const std::string& sp);
    int GetStationRouteId (const std::string& station, const std::string& sr);
    int GetTrackCircuitId (const std::string& tc);
    Resource* GetResource(int) const;
    Railway();
private:

    std::unordered_map<int, std::unique_ptr<Track>> m_tracks;
    std::unordered_map<int, std::unique_ptr<Station>> m_stations;
    std::unordered_map<int, std::unique_ptr<Train>> m_trains;
    std::unordered_map<int, std::unique_ptr<Resource>> m_resources;
    std::unordered_map<std::string, int> m_stationNameToId;
    std::unordered_map<std::string, int> m_trackNameToId;
    std::unordered_map<std::string, int> m_trainNameToId;
    std::unordered_map<std::string, int> m_trackCircuitToId;
};

inline int Railway::GetStationCount() const {
    return m_stations.size();
}

Station* GetStation(const std::string&);
Station* GetStation(int id);

inline Resource* Railway::GetResource(int id) const {
    auto it = m_resources.find(id);
    if (it == m_resources.end())
        GLIB_FAIL("Unknown resource with id = " << id);
    return it->second.get();
}
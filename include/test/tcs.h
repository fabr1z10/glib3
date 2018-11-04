#include <xml/tinyxml2.h>
#include <string>
#include <gfx/error.h>
#include <vector>
#include <unordered_map>
#include <memory>


typedef long ResourceId;



//class Activity {
//public:
//    void AddEdgeTo (Activity* other) {
//        m_next.push_back(other);
//        other->m_prev.push_back(this);
//    }
//    virtual ~Activity(){}
//    virtual void Run() {}
//private:
//    std::vector<Activity*> m_next;
//    std::vector<Activity*> m_prev;
//    long _etd;
//    long _theoetd;
//
//};
//
//class ResourceActivity : public Activity {
//public:
//    ResourceActivity(){}
//    std::string GetTrainId() const { return m_train; }
//    Resource* GetResource() const { return m_resource; }
//protected:
//    std::string m_train;
//    Resource* m_resource;
//};
//
//class SourceActivity : public Activity {
//public:
//
//};
//
//class TrackActivity : public ResourceActivity {
//public:
//    TrackActivity(Track* track) : ResourceActivity() {
//        m_resource = track;
//    }
//private:
//    Track* m_track;
//};
//
//class StationActivity : public ResourceActivity {
//public:
//    StationActivity(Station* station) : ResourceActivity() {
//        m_resource = station;
//    }
//private:
//    Station* m_station;
//};
//
//class TCSGraph {
//public:
//    void AddNode (std::shared_ptr<ResourceActivity> activity) {
//        m_trainActivities[activity->GetTrainId()][activity->GetResource()->GetId()] = activity;
//    }
//    Activity* GetActivity (const std::string& train, long resource);
//private:
//    std::unordered_map<std::string, std::unordered_map<long, std::shared_ptr<Activity>>> m_trainActivities;
//};
//
//inline Activity* TCSGraph::GetActivity (const std::string& train, long resource) {
//    return m_trainActivities[train][resource].get();
//}
//
//class Data {
//public:
//
//    Track* GetTrack(const std::string& id) {
//        auto it = m_trackToResId.find(id);
//        if (it == m_trackToResId.end())
//            GLIB_FAIL("Cannot find track " << id);
//        return m_tracks[it->second].get();
//    }
//
//    Station* GetStation(const std::string& id) {
//        auto it = m_stationToResId.find(id);
//        if (it == m_stationToResId.end())
//        GLIB_FAIL("Cannot find station " << id);
//        return m_stations[it->second].get();
//    }
//
//private:
//    std::unordered_map<std::string, long> m_stationToResId;
//    std::unordered_map<std::string, long> m_trackToResId;
//
//    std::unordered_map<long, std::unique_ptr<Track>> m_tracks;
//    std::unordered_map<long, std::unique_ptr<Station>> m_stations;
//};

void Run(const std::string& status);
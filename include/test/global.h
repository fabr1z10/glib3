#pragma once
#include <gfx/singleton.h>
#include <string>
#include <test/railway.h>

class Config : public Singleton<Config> {
public:
    void SetHomeDir(const std::string&);
    std::string GetHomeDir() const;
    Railway& GetRailway() { return m_railway; }

private:
    std::string m_homeDirectory;
    Railway m_railway;

};

inline void Config::SetHomeDir(const std::string& homeDir){
    m_homeDirectory = homeDir;
}

inline std::string Config::GetHomeDir() const {
    return m_homeDirectory;
}

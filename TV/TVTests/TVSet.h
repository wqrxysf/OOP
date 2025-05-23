#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <optional>

class TVSet 
{
public:
    bool TurnOn();
    bool TurnOff();
    bool IsOn() const;

    bool SelectChannel(int channel);
    bool SelectChannel(const std::string& name);

    bool SetChannelName(int channel, const std::string& name);
    bool DeleteChannelName(const std::string& name);

    std::optional<std::string> GetChannelName(int channel) const;
    std::optional<int> GetChannelByName(const std::string& name) const;

    int GetCurrentChannel() const;
    std::map<int, std::string> GetAllNamedChannels() const;

private:
    bool m_isOn = false;
    int m_currentChannel = 0;
    int m_lastChannel = 1;

    std::unordered_map<int, std::string> m_channelNames;
    std::unordered_map<std::string, int> m_nameToChannel;

    std::string NormalizeName(const std::string& name) const;
};

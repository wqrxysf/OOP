#include "TVSet.h"
#include <algorithm>
#include <cctype>
#include <sstream>

bool TVSet::TurnOn() {
    if (!m_isOn) {
        m_isOn = true;
        m_currentChannel = m_lastChannel;
        return true;
    }
    return false;
}

bool TVSet::TurnOff() {
    if (m_isOn) {
        m_isOn = false;
        m_lastChannel = m_currentChannel;
        m_currentChannel = 0;
        return true;
    }
    return false;
}

bool TVSet::IsOn() const {
    return m_isOn;
}

bool TVSet::SelectChannel(int channel) {
    if (!m_isOn || channel < 1 || channel > 99) return false;
    m_currentChannel = channel;
    return true;
}

bool TVSet::SelectChannel(const std::string& name) {
    if (!m_isOn) return false;
    auto it = m_nameToChannel.find(NormalizeName(name));
    if (it == m_nameToChannel.end()) return false;
    m_currentChannel = it->second;
    return true;
}

int TVSet::GetCurrentChannel() const {
    return m_isOn ? m_currentChannel : 0;
}

bool TVSet::SetChannelName(int channel, const std::string& name) {
    if (!m_isOn || channel < 1 || channel > 99) return false;

    std::string normName = NormalizeName(name);
    if (normName.empty()) return false;

    // избавляемся от старой привязки
    for (auto it = m_nameToChannel.begin(); it != m_nameToChannel.end(); ) {
        if (it->second == channel) {
            m_channelNames.erase(it->second);
            it = m_nameToChannel.erase(it);
        }
        else {
            ++it;
        }
    }

    // Удалить существующую ассоциацию с этим именем
    auto prevChannel = m_nameToChannel.find(normName);
    if (prevChannel != m_nameToChannel.end()) {
        m_channelNames.erase(prevChannel->second);
        m_nameToChannel.erase(prevChannel);
    }

    m_channelNames[channel] = normName;
    m_nameToChannel[normName] = channel;
    return true;
}

bool TVSet::DeleteChannelName(const std::string& name) {
    if (!m_isOn) return false;
    std::string normName = NormalizeName(name);
    auto it = m_nameToChannel.find(normName);
    if (it == m_nameToChannel.end()) return false;

    m_channelNames.erase(it->second);
    m_nameToChannel.erase(it);
    return true;
}

std::optional<std::string> TVSet::GetChannelName(int channel) const {
    if (!m_isOn || channel < 1 || channel > 99) return std::nullopt;
    auto it = m_channelNames.find(channel);
    if (it != m_channelNames.end())
        return it->second;
    return std::nullopt;
}

std::optional<int> TVSet::GetChannelByName(const std::string& name) const {
    if (!m_isOn) return std::nullopt;
    std::string normName = NormalizeName(name);
    auto it = m_nameToChannel.find(normName);
    if (it != m_nameToChannel.end())
        return it->second;
    return std::nullopt;
}

std::string TVSet::NormalizeName(const std::string& rawName) const{
    std::istringstream iss(rawName);
    std::string word, result;
    while (iss >> word) {
        if (!result.empty()) result += ' ';
        result += word;
    }
    return result;
}

std::map<int, std::string> TVSet::GetAllNamedChannels() const {
    if (!m_isOn)
        return {};

    std::map<int, std::string> result(m_channelNames.begin(), m_channelNames.end());
    return result;
}


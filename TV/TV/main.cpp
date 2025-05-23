#include <iostream>
#include <sstream>
#include "TVSet.h"

const std::string ERROR_MESSAGE = "ERROR";
const std::string TURN_ON_MESSAGE = "TV is turned on";
const std::string TURN_OFF_MESSAGE = "TV is turned off";
const std::string SWITCH_MESSAGE = "Channel switched to: ";
const std::string SET_MESSAGE = "Channel name set: ";
const std::string DELETE_MESSAGE = "Channel name deleted: ";
const std::string GET_CHANNEL_MESSAGE = "Channel for name ";
const std::string INFO_MESSAGE = "Channel is: ";

int main()
{
    TVSet tv;
    std::string line;

    while (std::getline(std::cin, line)) 
    {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "TurnOn") 
        {
            std::cout << (tv.TurnOn() ? TURN_ON_MESSAGE : TURN_ON_MESSAGE) << '\n';
        }
        else if (command == "TurnOff") 
        {
            std::cout << (tv.TurnOff() ? TURN_OFF_MESSAGE : TURN_OFF_MESSAGE) << '\n';
        }
        else if (command == "SelectChannel") 
        {
            std::string arg;
            if (!(iss >> arg)) 
            {
                std::cout << ERROR_MESSAGE << '\n';
                continue;
            }
            try 
            {
                int channel = std::stoi(arg);
                if (tv.SelectChannel(channel)) 
                {
                    std::cout << SWITCH_MESSAGE << channel << '\n';
                }
                else {
                    std::cout << ERROR_MESSAGE << '\n';
                }
            }
            catch (...) 
            {
                if (tv.SelectChannel(arg)) 
                {
                    std::cout << SWITCH_MESSAGE << arg << '\n';
                }
                else {
                    std::cout << ERROR_MESSAGE << '\n';
                }
            }
        }
        else if (command == "SetChannelName") 
        {
            int number;
            std::string name;
            if (!(iss >> number) || !std::getline(iss, name)) 
            {
                std::cout << ERROR_MESSAGE << '\n';
                continue;
            }
            if (tv.SetChannelName(number, name)) 
            {
                std::cout << SET_MESSAGE << number << " - " << tv.GetChannelName(number).value() << '\n';
            }
            else {
                std::cout << ERROR_MESSAGE << '\n';
            }
        }
        else if (command == "DeleteChannelName") 
        {
            std::string name;
            if (!std::getline(iss, name)) 
            {
                std::cout << ERROR_MESSAGE << '\n';
                continue;
            }
            if (tv.DeleteChannelName(name)) 
            {
                std::cout << DELETE_MESSAGE << name << '\n';
            }
            else 
            {
                std::cout << ERROR_MESSAGE << '\n';
            }
        }
        else if (command == "GetChannelName")
        {
            int number;
            if (!(iss >> number))
            {
                std::cout << ERROR_MESSAGE << '\n';
                continue;
            }
            auto name = tv.GetChannelName(number);
            if (name) 
            {
                std::cout << "Channel " << number << " name: " << *name << '\n';
            }
            else {
                std::cout << ERROR_MESSAGE << '\n';
            }
        }
        else if (command == "GetChannelByName")
        {
            std::string name;
            if (!std::getline(iss, name)) 
            {
                std::cout << ERROR_MESSAGE << '\n';
                continue;
            }
            auto number = tv.GetChannelByName(name);
            if (number)
            {
                std::cout << GET_CHANNEL_MESSAGE << name << ": " << *number << '\n';
            }
            else
            {
                std::cout << ERROR_MESSAGE << '\n';
            }
        }
        else if (command == "Info") 
        {
            if (!tv.IsOn()) 
            {
                std::cout << TURN_OFF_MESSAGE << '\n';
            }
            else
            {
                std::cout << TURN_ON_MESSAGE << '\n';
                std::cout << INFO_MESSAGE << tv.GetCurrentChannel() << '\n';
                auto namedChannels = tv.GetAllNamedChannels();
                for (const auto& [num, name] : namedChannels) 
                {
                    std::cout << num << " - " << name << '\n';
                }
            }
        }
        else 
        {
            std::cout << ERROR_MESSAGE << '\n';
        }
    }

    return 0;
}

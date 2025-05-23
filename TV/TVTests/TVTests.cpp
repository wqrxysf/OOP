#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TVSet.h"

// turm
TEST_CASE("TV turns on and off") 
{
    TVSet tv;

    REQUIRE_FALSE(tv.IsOn());

    REQUIRE(tv.TurnOn());
    REQUIRE(tv.IsOn());

    // Второй раз — уже включён
    REQUIRE_FALSE(tv.TurnOn());

    REQUIRE(tv.TurnOff());
    REQUIRE_FALSE(tv.IsOn());

    // Второй раз — уже выключен
    REQUIRE_FALSE(tv.TurnOff());
}

// select
TEST_CASE("SelectChannel by number") 
{
    TVSet tv;

    REQUIRE_FALSE(tv.SelectChannel(5)); // выключен

    tv.TurnOn();
    REQUIRE_FALSE(tv.SelectChannel(0));  // < 1
    REQUIRE_FALSE(tv.SelectChannel(100)); // > 99

    REQUIRE(tv.SelectChannel(25));
    REQUIRE(tv.GetCurrentChannel() == 25);
}

// select 2
TEST_CASE("SelectChannel by name") 
{
    TVSet tv;
    tv.TurnOn();

    REQUIRE_FALSE(tv.SelectChannel("MTV")); // ещё не задано имя

    tv.SetChannelName(7, "MTV");
    REQUIRE(tv.SelectChannel("  MTV  ")); // нормализованное имя
    REQUIRE(tv.GetCurrentChannel() == 7);
}

// SetChannelName / GetChannelName / GetChannelByName
TEST_CASE("Set/Get channel name")
{
    TVSet tv;
    tv.TurnOn();

    REQUIRE(tv.SetChannelName(10, "CNN"));
    REQUIRE(tv.GetChannelName(10).has_value());
    REQUIRE(tv.GetChannelName(10).value() == "CNN");

    REQUIRE(tv.GetChannelByName(" CNN ").has_value());
    REQUIRE(tv.GetChannelByName(" CNN ").value() == 10);
}

// name conflict
TEST_CASE("Reassigning channel names clears old links") 
{
    TVSet tv;
    tv.TurnOn();

    REQUIRE(tv.SetChannelName(1, "Discovery"));
    REQUIRE(tv.SetChannelName(2, "Discovery")); // имя переезжает к 2

    REQUIRE_FALSE(tv.GetChannelName(1).has_value());
    REQUIRE(tv.GetChannelByName("Discovery").value() == 2);
}

// DeleteChannelName
TEST_CASE("Delete channel name") 
{
    TVSet tv;
    tv.TurnOn();

    tv.SetChannelName(3, "BBC");
    REQUIRE(tv.DeleteChannelName(" BBC "));
    REQUIRE_FALSE(tv.GetChannelByName("BBC").has_value());
    REQUIRE_FALSE(tv.GetChannelName(3).has_value());
}

//  GetAllNamedChannels
TEST_CASE("GetAllNamedChannels returns sorted map") 
{
    TVSet tv;
    tv.TurnOn();

    tv.SetChannelName(10, "BBC");
    tv.SetChannelName(5, "MTV");

    auto all = tv.GetAllNamedChannels();

    REQUIRE(all.size() == 2);
    auto it = all.begin();
    REQUIRE(it->first == 5);
    REQUIRE(it->second == "MTV");
    ++it;
    REQUIRE(it->first == 10);
    REQUIRE(it->second == "BBC");
}

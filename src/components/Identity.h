#pragma once
#include <string>
#include <cstdint>
enum class IdentityType : uint8_t
{
    UNKNOWN,  // 群友
    LORD,     // 群主
    LOYALIST, // 管理员
    REBEL,    // 狂徒
    PestMan   // 害虫
};
enum class Faction : uint8_t
{
    NONE = 0,
    ALLY = 1,
    ENEMY = 2
};

struct Identity
{
    std::string name;
    uint32_t id;
    std::string tag;
};
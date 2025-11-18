/**
 * ************************************************************************
 *
 * @file Identity.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-14
 * @version 0.1
 * @brief 身份定义
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */
#pragma once

#include <entt/entity/fwd.hpp>
#include <string>
#include <cstdint>
#include <functional>
#include <entt/entt.hpp>
#include "../common/Common.h"
#include "Skill.h"

struct MetaCharacterInfo
{
    std::string name;
    uint32_t id;
    std::string tag;
    bool Gender;
};

struct Identity
{
    IdentityType type;
    bool revealed = false; // 是否公开身份
};

struct Faction
{
    FactionType type;
};

struct Skills
{
    std::vector<Skill> skillList;
};

struct HandCards
{
    std::vector<entt::entity> handCards;
};

struct Equipments
{
    entt::entity weapon = entt::null;
    entt::entity armor = entt::null;
    entt::entity attackhorse = entt::null;
    entt::entity defensehorse = entt::null;
};

struct Attributes
{
    uint32_t maxHealth = 4;
    uint32_t currentHealth = 4;
    uint32_t attackPower = 1;
    uint32_t defense = 0;
    uint32_t attackRange = 1;
    uint32_t movement = 1;
    uint8_t rank = 0;
};


struct Status
{
    uint8_t duration = 0;   // 持续回合数，0表示永久
    TurnPhase appliedPhase; // 状态应用的阶段
    StatusType type;
};

struct StatusFlags
{
    std::vector<Status> statusList; // 角色状态列表
};

inline entt::entity createCharacter(entt::registry& reg, std::string name, IdentityType identity, FactionType faction)
{
    auto e = reg.create();

    reg.emplace<MetaCharacterInfo>(e, MetaCharacterInfo{name, (uint32_t)e});
    reg.emplace<Identity>(e, Identity{identity, false});
    reg.emplace<Faction>(e, Faction{faction});
    reg.emplace<Attributes>(e);
    reg.emplace<StatusFlags>(e);
    reg.emplace<Skills>(e);
    reg.emplace<HandCards>(e);
    reg.emplace<Equipments>(e);

    return e;
}

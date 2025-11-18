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
#include "src/common/Common.h"

struct MetaCharacterInfo
{
    std::string name;
    uint32_t id;
    std::string tag;
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

/********** about Effect ********* */
struct Effect
{
    std::function<void(entt::entity user, entt::entity target, entt::registry& reg)> apply;
};

struct Skill
{
    std::string name;
    std::function<void(entt::registry&, entt::entity&, entt::any)> onTrigger; // or custom signature
};

struct MetaCardInfo
{
    std::string name;
    std::string description; // 新增描述字段
    CardType type;
    std::function<void(entt::registry&, entt::entity&, entt::entity&)> onUse; // or custom signature
};

struct CardCost
{
    int mana = 0;
    int energy = 0;
};
struct CardTarget
{
    bool need_target = true;
    int max_targets = 1;
    std::function<bool(entt::entity)> filter; // 目标筛选规则
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
    int maxHealth = 4;
    int currentHealth = 4;
    int attackPower = 1;
    int defense = 0;
};

enum class StatusFlag : uint8_t
{
    POISONED,
    STUNNED,
    SHIELDED
};
struct Status
{
    uint8_t duration = 0;   // 持续回合数，0表示永久
    TurnPhase appliedPhase; // 状态应用的阶段
    StatusFlag flag;
};

struct StatusFlags
{
    std::vector<Status> statusList; // 角色状态列表
};

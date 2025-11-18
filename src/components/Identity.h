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
#include <cstddef>
#include <string>
#include <cstdint>
#include <functional>
#include <entt/entt.hpp>
enum class IdentityType : uint8_t
{
    MEMBER,
    OWNER,
    ADMIN,
    ROGUE,
    PESTMAN

};
enum class FactionType : uint8_t
{
    VIRGIN,
    PLAYMAN,
    BOOMER
};

struct CharacterInfo
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

struct Skill
{
    std::string name;
    std::function<void(entt::registry&, entt::entity&, entt::any)> onTrigger; // or custom signature
};

enum class SkillTriggerTiming : uint8_t
{
    TURN_START,        // 开始阶段
    TURN_END,          // 结束阶段
    DAMAGE_DEAL,       // 造成伤害
    DAMAGE_TAKEN,      // 受到伤害
    TURNPHASE_START,   // 回合开始阶段
    TURNPHASE_JUDGE,   // 判定阶段
    TURNPHASE_DRAW,    // 摸牌阶段
    TURNPHASE_PLAY,    // 出牌阶段
    TURNPHASE_DISCARD, // 弃牌阶段
    TURNPHASE_END      // 回合结束阶段
};

enum class SkillType : uint8_t
{
    PASSIVE,  // 被动技能
    ACTIVE,   // 主动技能
    REACTIVE, // 反应技能
    LOCKED,
    PHASELIMITED
};

// 回合的阶段
enum class TurnPhase : uint8_t
{
    START,   // 回合开始阶段
    JUDGE,   // 判定阶段
    DRAW,    // 摸牌阶段
    PLAY,    // 出牌阶段
    DISCARD, // 弃牌阶段
    END      // 回合结束阶段
};

enum class CardType : uint8_t
{
    BASIC,
    TRICK,
    EQUIPMENT
};

struct Card
{
    std::string name;
    CardType type;
    std::function<void(entt::registry&, entt::entity&, entt::entity&)> onUse; // or custom signature
};

struct Skills
{
    std::vector<Skill> skillList; // 角色技能列表
};

struct HandCards
{
    std::vector<Card> handCards; // 手牌列表
};

struct Equipments
{
    std::vector<Card> equipmentCards; // 装备区牌列表
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

entt::entity createCharacter(entt::registry& reg, std::string name, IdentityType identity, FactionType faction)
{
    auto e = reg.create();

    reg.emplace<CharacterInfo>(e, CharacterInfo{name, (uint32_t)e});
    reg.emplace<Identity>(e, Identity{identity, false});
    reg.emplace<Faction>(e, Faction{faction});
    reg.emplace<Attributes>(e);
    reg.emplace<StatusFlags>(e);
    reg.emplace<Skills>(e);
    reg.emplace<HandCards>(e);
    reg.emplace<Equipments>(e);

    return e;
}

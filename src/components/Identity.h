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
};

struct Faction
{
    FactionType type;
};

/**
 * ************************************************************************
 * @brief
 * 技能定义
 * 名称
 *  触发效果
 *  发动时机（回合开始前/）
 *  持续回合/不持续

 * ************************************************************************
 */
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
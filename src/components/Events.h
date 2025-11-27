/**
 * ************************************************************************
 *
 * @file Event.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-18
 * @version 0.1
 * @brief 事件定义
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */
#pragma once

#include "src/common/Common.h"
#include <cstddef>
#include <cstdint>
#include <entt/entity/entity.hpp>
#include <entt/entt.hpp>
#include <string>
#include <vector>

namespace events
{

struct ShowWindow
{
};

// 0. 测试事件
struct GameEvent
{
    int value = 0;
};

struct CharacterDeath
{
    entt::entity character;
};

struct CanPlayCard
{
    entt::entity player = entt::null;
    entt::entity card = entt::null;
    bool canceled = false;
};

struct CalculateDamage
{
    entt::entity source;
    entt::entity target;
    int baseDamage;
};

struct ChooseTarget
{
    entt::entity player;
    std::vector<entt::entity> availableTargets;
};

// 3. 动作事件（可能被取消）
struct Damage
{
    entt::entity from;
    entt::entity to;
    int amount;
};

struct CardUsed
{
    entt::entity user;
    entt::entity target;
    entt::entity card;
};

struct LostHealth

{
    entt::entity character; // 失去生命值的角色
    int amount;             // 失去的生命值数值
};

struct TurnPhase
{
    entt::entity player;      // 当前回合角色
    ::TurnPhase currentPhase; // 当前阶段，参考 TurnPhase 枚举
};

struct CardPlayed // 打出牌事件
{
    entt::entity player; // 出牌角色
    entt::entity card;   // 出的牌
};

struct CardChipIn
{                        // 拼点事件
    entt::entity player; // 拼点角色
    entt::entity card;   // 拼点的牌
};

struct CardDrawn
{
    entt::entity player; // 摸牌角色
    entt::entity card;   // 摸到的牌
    uint8_t count;       // 摸牌数量
};

struct CardDiscarded
{
    entt::entity player; // 弃牌角色
    entt::entity card;   // 弃掉的牌
    uint8_t count;       // 弃牌数量
};

struct NearDeath
{
    entt::entity killer;    // 凶手角色
    entt::entity character; // 濒死角色
    int32_t currentHealth;  // 当前生命值
};

struct GameStart
{
    // 可以添加游戏开始时需要的信息
    uint8_t playerCount; // 玩家数量
};

struct GameEnd
{
    std::string reason; // 游戏结束原因
};

struct UsingAttackCard
{
    entt::entity attacker; // 攻击者
    entt::entity defender; // 防御者
    size_t damage;         // 伤害值
};

struct CheckCardToResponse
{
    entt::entity player;  // 需要响应的角色
    std::string cardName; // 需要响应的牌名
    bool canRespond;      // 是否可以响应
};

struct TurnStartEvent
{
    entt::entity player; // 当前回合角色
};

struct DamagePrevention
{
    entt::entity source; // 伤害来源角色
    entt::entity healer; // 预防伤害的角色
    entt::entity target; // 受到伤害的角色
    int amount;          // 预防的伤害数值
};

struct DamageRedirection
{
    entt::entity source;         // 伤害来源角色
    entt::entity originalTarget; // 原始受伤角色
    entt::entity newTarget;      // 新的受伤角色
    int amount;                  // 重定向的伤害数值
};

struct DetailFinish
{
    entt::entity player;             // 当前回合角色
    std::vector<entt::entity> cards; // 结算的牌
};

} // namespace events
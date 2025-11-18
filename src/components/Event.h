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
#include <cstdint>
#include <entt/entt.hpp>

struct DamageEvent
{
    entt::entity from; // 伤害来源
    entt::entity to;   // 伤害目标
    int amount;        // 伤害数值
};

struct TurnPhaseEvent
{
    entt::entity player;    // 当前回合角色
    TurnPhase currentPhase; // 当前阶段，参考 TurnPhase 枚举
};

struct CharacterDeathEvent
{
    entt::entity character; // 死亡角色
};

struct CardUsedEvent
{
    entt::entity user;   // 使用牌的角色
    entt::entity target; // 牌的目标角色
    entt::entity card;   // 使用的牌
};

struct CardDrawnEvent
{
    entt::entity player; // 摸牌角色
    entt::entity card;   // 摸到的牌
    uint8_t count;       // 摸牌数量
};

struct CardDiscardedEvent
{
    entt::entity player; // 弃牌角色
    entt::entity card;   // 弃掉的牌
    uint8_t count;       // 弃牌数量
};

struct GameStartEvent
{
    // 可以添加游戏开始时需要的信息
    uint8_t playerCount; // 玩家数量
};

struct GameEndEvent
{
    std::string reason; // 游戏结束原因
};

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
#include <entt/entt.hpp>

struct DamageEvent
{
    entt::entity from; // 伤害来源
    entt::entity to;   // 伤害目标
    int amount;        // 伤害数值
};

struct TurnPhaseEvent
{
    entt::entity player; // 当前回合角色
    uint8_t phase;       // 当前阶段，参考 TurnPhase 枚举
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

struct GameStartEvent
{
    // 可以添加游戏开始时需要的信息
};

struct GameEndEvent
{
    std::string reason; // 游戏结束原因
};
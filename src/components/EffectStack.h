/**
 * ************************************************************************
 *
 * @file EffectStack.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-19
 * @version 0.1
 * @brief  效果栈定义 每个时机压栈，按顺序解析执行，时机结束出栈 时机开始时清空
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#include <vector>
#pragma once
#include <entt/entt.hpp>
#include <stack>

struct EffectStack
{
    std::stack<entt::delegate<void(entt::entity, std::span<entt::entity>, entt::registry&)>> effects;
};


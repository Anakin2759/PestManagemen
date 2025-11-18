/**
 * ************************************************************************
 *
 * @file GameContext.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-18
 * @version 0.1
 * @brief 游戏上下文定义
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */
#pragma once
#include "spdlog/logger.h"
#include <entt/entt.hpp>
#include "src/utils/CreateLogger.h"
struct GameContext
{
    entt::registry registry;     // 实体组件系统注册表
    entt::dispatcher dispatcher; // 事件分发器
    std::shared_ptr<spdlog::logger> logger = CreateRollingLogger();
};
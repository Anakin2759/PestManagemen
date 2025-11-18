/**
 * ************************************************************************
 *
 * @file TurnSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-18
 * @version 0.1
 * @brief entt-based 回合管理系统
    enable 函数初始化回合管理器，注册函数到事件分发器
    disable 函数清理回合管理器，注销函数
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once

#include <entt/entt.hpp>
#include "src/context/GameContext.h"
class TurnManager
{
public:
    void work(GameContext& context);

private:
};
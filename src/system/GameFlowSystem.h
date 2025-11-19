/**
 * ************************************************************************
 *
 * @file GameFlowSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-18
 * @version 0.1
 * @brief 游戏流程控制系统
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once

#include "src/context/GameContext.h"
#include "src/components/GameData.h"
#include "src/components/Event.h"
class GameFlowSystem
{
public:
    void start(GameContext& context)
    {
        // 初始化游戏状态，发起游戏开始事件等
        context.registry.ctx().emplace<GameData>();
    };
    void pause(GameContext& context);
    void stop(GameContext& context);
};
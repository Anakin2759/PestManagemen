/**
 * ************************************************************************
 *
 * @file CardManagementSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-19
 * @version 0.1
 * @brief 卡牌管理系统（发牌员）
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once

#include "src/context/GameContext.h"
class CardManagementSystem
{
public:
    void shuffleDeck(GameContext& context);      // 洗牌
    void dealInitialHands(GameContext& context); // 给每个玩家发初始手牌
    void drawCard(GameContext& context);         // 玩家摸牌
    void discardCard(GameContext& context);      // 玩家弃牌
    void useCard(GameContext& context);          // 玩家使用牌
};
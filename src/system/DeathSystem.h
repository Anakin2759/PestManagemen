/**
 * ************************************************************************
 *
 * @file DeathSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-18
 * @version 0.1
 * @brief 死亡处理系统
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once
#include "src/context/GameContext.h"
#include "src/components/Event.h"
#include "src/components/Character.h"
class DanageAndDeathSystem
{
public:
    static void handleDeath(GameContext& context, entt::entity character)
    {
        if (!context.registry.valid(character))
        {
            return;
        } // 实体无效

        if (!context.registry.all_of<Attributes>(character))
        {
            return;
        } // 没有属性组件

        auto& attr = context.registry.get<Attributes>(character);

        if (!attr.isAlive)
        {
            return;
        }
        attr.isAlive = false;

        context.dispatcher.trigger(CharacterDeathEvent{character});

        // 可选：将角色从回合队列或行动队列中移除
        // context.removeFromTurnQueue(character);
    }
};
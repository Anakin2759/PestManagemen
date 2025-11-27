/**
 * ************************************************************************
 *
 * @file UseCardSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-27
 * @version 0.1
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once
#include <entt/entt.hpp>
#include "src/context/GameContext.h"
#include "src/components/Events.h"
#include "src/components/Card.h"

class UseCardSystem
{
public:
    explicit UseCardSystem(GameContext& context) : m_context(context) {};
    void registerEvents() { m_context.dispatcher.sink<events::CardUsed>().connect<&UseCardSystem::onCardUsed>(this); };
    void unregisterEvents()
    {
        m_context.dispatcher.sink<events::CardUsed>().disconnect<&UseCardSystem::onCardUsed>(this);
    };

private:
    void onCardUsed(const events::CardUsed& event)
    {
        // 处理卡牌使用事件的逻辑
    }

    GameContext& m_context;
};
/**
 * ************************************************************************
 *
 * @file DeckSystem.h
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
#include "src/components/Deck.h"
#include "src/components/Events.h"

class DeckSystem
{
public:
    explicit DeckSystem(GameContext& context) : m_context(context)
    {
        m_context.logger->info("DeckSystem 初始化");
        m_context.registry.ctx().emplace<Deck>();
    };
    void registerEvents() {

    };
    void unregisterEvents() {

    };

private:
    GameContext& m_context;
};
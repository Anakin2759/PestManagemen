/**
 * ************************************************************************
 *
 * @file ResponseSystem.h
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
#include "src/components/Character.h"
class ResponseSystem
{
public:
    explicit ResponseSystem(GameContext& context) : m_context(context) {};
    void registerEvents()
    {
        m_context.dispatcher.sink<events::UsingAttackCard>().connect<&ResponseSystem::onAttack>(this);
    };
    void unregisterEvents()
    {
        m_context.dispatcher.sink<events::UsingAttackCard>().disconnect<&ResponseSystem::onAttack>(this);
    };

private:
    void onAttack(const events::UsingAttackCard& event) const
    {
        auto attackerName = m_context.registry.get<MetaCharacterInfo>(event.attacker).name;
        auto defenderName = m_context.registry.get<MetaCharacterInfo>(event.defender).name;
        // 处理攻击事件的逻辑
        m_context.logger->info("{}对{}使用了一张杀", attackerName, defenderName);
    }

    bool onCheckDodgeCard(const events::CheckCardToResponse& event) const { return false; }

    GameContext& m_context;
};
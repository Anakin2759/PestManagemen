/**
 * ************************************************************************
 *
 * @file PlayerSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-25
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
class PlayerSystem
{
public:
    explicit PlayerSystem(GameContext& context) : m_context(context) {};
    void registerEvents() {  };
    void unregisterEvents() {  };
private:
    GameContext& m_context;
};
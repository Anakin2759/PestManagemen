#pragma once

#include <entt/entt.hpp>
#include "context/GameContext.h"
#include "src/systems/ISystem.h"
#include "src/context/GameContext.h"

class SystemManager
{
public:
    explicit SystemManager(GameContext& context) : m_context(context) {}
    void addSystem(auto system)
    {
        m_context.logger->info("添加系统");
        m_systems.emplace_back(std::move(system));
        m_context.logger->info("系统添加，当前系统数量：{}", m_systems.size());
    }

    void registryAll()
    {
        for (auto& system : m_systems)
        {
            system->registerEvents();
        }
    }

    void unregisterAll()
    {
        for (auto& system : m_systems)
        {
            system->unregisterEvents();
        }
    }

private:
    std::vector<entt::poly<ISystem>> m_systems;
    GameContext& m_context;
};

#include "SystemManager.h"
#include <mimalloc-new-delete.h>

#include <entt/entt.hpp>
#include "src/context/GameContext.h"
#include "src/systems/ISystem.h"
#include "src/systems/ViewSystem.h"
#include <iostream>
int main()
{
    std::cout << "Pest Management System Starting..." << std::endl;
    GameContext gameContext;
    gameContext.logger->info("创建上下文环境完成");
    SystemManager systemManager(gameContext);

    gameContext.logger->info("初始化系统管理器");
    systemManager.addSystem(entt::poly<ISystem>(ViewSystem(gameContext)));
    gameContext.logger->info("系统管理器添加系统完成");
    systemManager.registryAll();
    gameContext.logger->info("系统管理器初始化完成，开始游戏主循环");
    gameContext.dispatcher.trigger<events::ShowWindow>();
    systemManager.unregisterAll();
    return 0;
}
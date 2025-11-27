/**
 * ************************************************************************
 *
 * @file ViewSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-19
 * @version 0.1
 * @brief 视图系统定义
    显示游戏界面，处理用户输入
    发出信号通知游戏逻辑系统
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */
#pragma once
#include <entt/entt.hpp>
#include "src/components/Events.h"
#include "src/context/GameContext.h"
#include "src/view/App.h"
#include <asio.hpp>
class ViewSystem
{
public:
    explicit ViewSystem(GameContext& context) : m_context(context) {};

    void registerEvents() { m_context.dispatcher.sink<events::ShowWindow>().connect<&ViewSystem::onShowWindow>(this); }
    void unregisterEvents()
    {
        m_context.dispatcher.sink<events::ShowWindow>().disconnect<&ViewSystem::onShowWindow>(this);
    }

private:
    void onShowWindow(events::ShowWindow event)
    {
        asio::post(m_context.threadPool,
                   [this]()
                   {
                       m_context.logger->info("界面展示");
                       App mw("sss", 1200, 800);
                       mw.run();
                   });
    };

    GameContext& m_context;
};
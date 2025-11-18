/**
 * ************************************************************************
 *
 * @file TurnSystem.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-18
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
#include "src/components/Event.h"

class TurnManager
{
public:
    TurnManager(entt::registry& r, entt::dispatcher& d) : reg(r), disp(d) {}

    void setPlayers(const std::vector<entt::entity>& players_) { players = players_; }
    void setPhases(const std::vector<TurnPhase>& p) { phases = p; }
    void setDrawCount(int c) { drawCount = c; }

    void startGame()
    {
        currentIndex = 0;
        round = 1;
        std::cout << "Game started with " << players.size() << " players.\n";
    }

    void runTurn()
    {
        if (players.empty())
            return;
        auto player = players[currentIndex];

        // 触发回合开始事件
        disp.trigger<TurnStartEvent>({player});

        for (auto phase : phases)
        {
            disp.trigger<PhaseStartEvent>({player, phase});

            // 摸牌阶段自动发事件
            if (phase == TurnPhase::DRAW)
            {
                disp.trigger<DrawEvent>({player, drawCount});
            }

            disp.trigger<PhaseEndEvent>({player, phase});
        }

        disp.trigger<TurnEndEvent>({player});

        advance();
    }

    entt::entity currentPlayer() const { return players.empty() ? entt::null : players[currentIndex]; }

private:
    void advance()
    {
        currentIndex = (currentIndex + 1) % players.size();
        if (currentIndex == 0)
            ++round;
    }

private:
    entt::registry& reg;
    entt::dispatcher& disp;
    std::vector<entt::entity> players;
    std::vector<TurnPhase> phases{TurnPhase::START, TurnPhase::DRAW, TurnPhase::PLAY, TurnPhase::END};
    size_t currentIndex = 0;
    int round = 0;
    int drawCount = 2;
};
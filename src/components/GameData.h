/**
 * ************************************************************************
 *
 * @file GameData.h
 * @author AnakinLiu (azrael2759@qq.com)
 * @date 2025-11-19
 * @version 0.1
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2025 AnakinLiu
 * For study and research only, no reprinting.
 * ************************************************************************
 */

#pragma once
#include <cstdint>
#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>
#include "src/common/Common.h"

struct GameData
{
    TurnPhase currentPhase = TurnPhase::START;
    GameMode mode = GameMode::CHANLLENGE_PEST;
    entt::entity currentPlayer = entt::null;
    uint32_t round = 0;
};
/**
 * ************************************************************************
 *
 * @file System.h
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

#include "proxy/v4/proxy_macros.h"
#include <proxy/proxy.h>
#include <entt/entt.hpp>
#include "src/context/GameContext.h"

PRO_DEF_MEM_DISPATCH(MemWork, Work);

struct ISystem : pro::facade_builder ::add_convention<MemWork, void(GameContext&) noexcept>::support_copy<
                     pro::constraint_level::nontrivial>::build
{
};

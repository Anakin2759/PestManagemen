/**
 * ************************************************************************
 *
 * @file Skill.h
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
#include <string>
#include <functional>
#include <entt/entt.hpp>

struct Effect
{
    std::function<void(entt::entity user, entt::entity target, entt::registry& reg)> apply;
};

struct Skill
{
    std::string name;
    std::function<void(entt::registry&, entt::entity&, entt::any)> onTrigger; // or custom signature
};

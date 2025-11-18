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
#include <entt/entity/fwd.hpp>
#include <string>
#include <functional>
#include <entt/entt.hpp>
#include <vector>
#include "src/common/Common.h"
struct Effect
{
    SkillType type;
    std::function<void(entt::entity user, std::vector<entt::entity> target, entt::registry& reg)> apply;
    std::vector<entt::entity> target;
};

struct MetaSkillInfo
{
    std::string name;
    std::string description; // 新增描述字段
};

struct SkillOwner
{
    entt::entity owner = entt::null;
};

inline entt::entity
    CreateSkill(const MetaSkillInfo& info, const Effect& effect, const SkillOwner& owner, entt::registry& reg)
{
    auto e = reg.create();
    reg.emplace<MetaSkillInfo>(e, info);
    reg.emplace<Effect>(e, effect);
    reg.emplace<SkillOwner>(e, owner);
    return e;
}

inline void WuShengFunc(entt::entity user, std::vector<entt::entity> target, entt::registry& reg) {

};
inline void WuShuangFunc(entt::entity user, std::vector<entt::entity> target, entt::registry& reg) {

};
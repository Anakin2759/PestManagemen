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
#include <cstdint>
#include <entt/entity/fwd.hpp>
#include <string>
#include <functional>
#include <entt/entt.hpp>
#include <vector>
#include "src/common/Common.h"
struct SkillEffect
{
    SkillType type;
    entt::delegate<void(entt::entity, std::span<entt::entity>, entt::registry&)> apply;
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

struct SkillTarget
{
    bool needTarget = true;
    uint8_t maxTargets = 1;
    uint8_t minTargets = 1;

    std::function<bool(entt::entity)> filter; // 目标筛选规则
};

inline entt::entity
    CreateSkill(const MetaSkillInfo& info, const SkillEffect& effect, const SkillOwner& owner, entt::registry& reg)
{
    auto e = reg.create();
    reg.emplace<MetaSkillInfo>(e, info);
    reg.emplace<SkillEffect>(e, effect);
    reg.emplace<SkillOwner>(e, owner);
    return e;
}

inline void WuShengFunc(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {

};
inline void WuShuangFunc(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {

};
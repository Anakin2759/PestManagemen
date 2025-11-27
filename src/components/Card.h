/**
 * ************************************************************************
 *
 * @file Card.h
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
#include <string>
#include <functional>
#include <entt/entt.hpp>
#include <vector>
#include "src/common/Common.h"

struct MetaCardInfo
{
    std::string name;
    std::string description; // 新增描述字段
    CardType type = CardType::BASIC;
};

struct CardCost
{
    uint32_t mana = 0;
    uint32_t energy = 0;
    uint32_t health = 0;
};
struct CardTarget
{
    bool needTarget = true;
    uint8_t maxTargets = 1;
    uint8_t minTargets = 1;
    uint8_t range = 0; // 0表示无限制

    std::function<bool(entt::entity)> filter; // 目标筛选规则
};

struct CardPointAndSuit
{
    uint8_t point = 0;               // 0表示无点数，1-13分别表示A到K
    SuitType suit = SuitType::JOKER; // JOKER表示无花色
};
struct CardEffect
{
    entt::delegate<void(entt::entity, std::span<entt::entity>, entt::registry&)> apply;
};

struct BasicCardTypeTag
{
    BasicCardType type;
};

struct TrickCardTypeTag
{
    TrickCardType type;
};

struct EquipCardTypeTag
{
    EquipCardType type;
};

inline entt::entity CreateCard(entt::registry& reg,
                               const MetaCardInfo& metaInfo,
                               const CardCost& cost,
                               const CardTarget& target,
                               const CardPointAndSuit& pointAndSuit,
                               const CardEffect& effect)
{
    auto e = reg.create();
    reg.emplace<MetaCardInfo>(e, metaInfo);
    reg.emplace<CardCost>(e, cost);
    reg.emplace<CardTarget>(e, target);
    reg.emplace<CardPointAndSuit>(e, pointAndSuit);
    reg.emplace<CardEffect>(e, effect);
    return e;
}

inline std::vector<entt::entity> CreateStandardDeck(entt::registry& reg)
{
    std::vector<entt::entity> deck;

    return deck;
}

inline void FireAttackEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现火攻效果的逻辑
};

inline void DismantleEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现过河拆桥效果的逻辑
};

inline void SupplyEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现借刀杀人效果的逻辑
};

inline void DuelEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现决斗效果的逻辑
};

inline void PeachEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现桃效果的逻辑
};

inline void SlashEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现杀效果的逻辑

};

inline void ThunderSlashEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现雷杀效果的逻辑
};

inline void FireSlashEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现火杀效果的逻辑
};

inline void AnalepticEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现酒效果的逻辑
};

inline void NullificationEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现无懈可击效果的逻辑
};

inline void PeachGardenEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现桃园结义效果的逻辑
};

inline void StealEffect(entt::entity user, std::span<entt::entity> target, entt::registry& reg) {
    // 实现顺手牵羊效果的逻辑
};
